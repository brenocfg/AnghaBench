#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct packet_wreg32 {int dummy; } ;
struct packet_lin_dma {int dummy; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_cs_parser {scalar_t__ user_cb_size; TYPE_2__* patched_cb; TYPE_1__* user_cb; } ;
struct goya_packet {int /*<<< orphan*/  header; } ;
typedef  enum packet_id { ____Placeholder_packet_id } packet_id ;
struct TYPE_4__ {scalar_t__ kernel_address; } ;
struct TYPE_3__ {scalar_t__ kernel_address; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  PACKET_CP_DMA 137 
#define  PACKET_FENCE 136 
 int PACKET_HEADER_PACKET_ID_MASK ; 
 int PACKET_HEADER_PACKET_ID_SHIFT ; 
#define  PACKET_LIN_DMA 135 
#define  PACKET_MSG_LONG 134 
#define  PACKET_MSG_PROT 133 
#define  PACKET_MSG_SHORT 132 
#define  PACKET_NOP 131 
#define  PACKET_STOP 130 
#define  PACKET_WREG_32 129 
#define  PACKET_WREG_BULK 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__* goya_packet_sizes ; 
 int goya_patch_dma_packet (struct hl_device*,struct hl_cs_parser*,struct packet_lin_dma*,struct packet_lin_dma*,scalar_t__*) ; 
 int goya_validate_wreg32 (struct hl_device*,struct hl_cs_parser*,struct packet_wreg32*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct goya_packet*,struct goya_packet*,scalar_t__) ; 

__attribute__((used)) static int goya_patch_cb(struct hl_device *hdev,
				struct hl_cs_parser *parser)
{
	u32 cb_parsed_length = 0;
	u32 cb_patched_cur_length = 0;
	int rc = 0;

	/* cb_user_size is more than 0 so loop will always be executed */
	while (cb_parsed_length < parser->user_cb_size) {
		enum packet_id pkt_id;
		u16 pkt_size;
		u32 new_pkt_size = 0;
		struct goya_packet *user_pkt, *kernel_pkt;

		user_pkt = (struct goya_packet *) (uintptr_t)
			(parser->user_cb->kernel_address + cb_parsed_length);
		kernel_pkt = (struct goya_packet *) (uintptr_t)
			(parser->patched_cb->kernel_address +
					cb_patched_cur_length);

		pkt_id = (enum packet_id) (
				(le64_to_cpu(user_pkt->header) &
				PACKET_HEADER_PACKET_ID_MASK) >>
					PACKET_HEADER_PACKET_ID_SHIFT);

		pkt_size = goya_packet_sizes[pkt_id];
		cb_parsed_length += pkt_size;
		if (cb_parsed_length > parser->user_cb_size) {
			dev_err(hdev->dev,
				"packet 0x%x is out of CB boundary\n", pkt_id);
			rc = -EINVAL;
			break;
		}

		switch (pkt_id) {
		case PACKET_LIN_DMA:
			rc = goya_patch_dma_packet(hdev, parser,
					(struct packet_lin_dma *) user_pkt,
					(struct packet_lin_dma *) kernel_pkt,
					&new_pkt_size);
			cb_patched_cur_length += new_pkt_size;
			break;

		case PACKET_WREG_32:
			memcpy(kernel_pkt, user_pkt, pkt_size);
			cb_patched_cur_length += pkt_size;
			rc = goya_validate_wreg32(hdev, parser,
					(struct packet_wreg32 *) kernel_pkt);
			break;

		case PACKET_WREG_BULK:
			dev_err(hdev->dev,
				"User not allowed to use WREG_BULK\n");
			rc = -EPERM;
			break;

		case PACKET_MSG_PROT:
			dev_err(hdev->dev,
				"User not allowed to use MSG_PROT\n");
			rc = -EPERM;
			break;

		case PACKET_CP_DMA:
			dev_err(hdev->dev, "User not allowed to use CP_DMA\n");
			rc = -EPERM;
			break;

		case PACKET_STOP:
			dev_err(hdev->dev, "User not allowed to use STOP\n");
			rc = -EPERM;
			break;

		case PACKET_MSG_LONG:
		case PACKET_MSG_SHORT:
		case PACKET_FENCE:
		case PACKET_NOP:
			memcpy(kernel_pkt, user_pkt, pkt_size);
			cb_patched_cur_length += pkt_size;
			break;

		default:
			dev_err(hdev->dev, "Invalid packet header 0x%x\n",
				pkt_id);
			rc = -EINVAL;
			break;
		}

		if (rc)
			break;
	}

	return rc;
}