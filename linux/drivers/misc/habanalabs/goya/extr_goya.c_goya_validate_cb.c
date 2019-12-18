#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct packet_wreg32 {int dummy; } ;
struct packet_msg_prot {int dummy; } ;
struct packet_lin_dma {int dummy; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_cs_parser {scalar_t__ patched_cb_size; scalar_t__ user_cb_size; TYPE_1__* user_cb; } ;
struct goya_packet {int /*<<< orphan*/  header; } ;
typedef  enum packet_id { ____Placeholder_packet_id } packet_id ;
struct TYPE_2__ {scalar_t__ kernel_address; } ;

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
 int goya_validate_dma_pkt_mmu (struct hl_device*,struct hl_cs_parser*,struct packet_lin_dma*) ; 
 int goya_validate_dma_pkt_no_mmu (struct hl_device*,struct hl_cs_parser*,struct packet_lin_dma*) ; 
 int goya_validate_wreg32 (struct hl_device*,struct hl_cs_parser*,struct packet_wreg32*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_validate_cb(struct hl_device *hdev,
			struct hl_cs_parser *parser, bool is_mmu)
{
	u32 cb_parsed_length = 0;
	int rc = 0;

	parser->patched_cb_size = 0;

	/* cb_user_size is more than 0 so loop will always be executed */
	while (cb_parsed_length < parser->user_cb_size) {
		enum packet_id pkt_id;
		u16 pkt_size;
		struct goya_packet *user_pkt;

		user_pkt = (struct goya_packet *) (uintptr_t)
			(parser->user_cb->kernel_address + cb_parsed_length);

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
		case PACKET_WREG_32:
			/*
			 * Although it is validated after copy in patch_cb(),
			 * need to validate here as well because patch_cb() is
			 * not called in MMU path while this function is called
			 */
			rc = goya_validate_wreg32(hdev,
				parser, (struct packet_wreg32 *) user_pkt);
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

		case PACKET_LIN_DMA:
			if (is_mmu)
				rc = goya_validate_dma_pkt_mmu(hdev, parser,
					(struct packet_lin_dma *) user_pkt);
			else
				rc = goya_validate_dma_pkt_no_mmu(hdev, parser,
					(struct packet_lin_dma *) user_pkt);
			break;

		case PACKET_MSG_LONG:
		case PACKET_MSG_SHORT:
		case PACKET_FENCE:
		case PACKET_NOP:
			parser->patched_cb_size += pkt_size;
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

	/*
	 * The new CB should have space at the end for two MSG_PROT packets:
	 * 1. A packet that will act as a completion packet
	 * 2. A packet that will generate MSI-X interrupt
	 */
	parser->patched_cb_size += sizeof(struct packet_msg_prot) * 2;

	return rc;
}