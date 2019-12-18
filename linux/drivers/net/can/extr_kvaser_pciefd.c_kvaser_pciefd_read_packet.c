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
typedef  int u8 ;
struct kvaser_pciefd_rx_packet {int* header; int /*<<< orphan*/  timestamp; } ;
struct kvaser_pciefd {TYPE_1__* pci; int /*<<< orphan*/ ** dma_data; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EIO ; 
 int KVASER_PCIEFD_PACKET_TYPE_SHIFT ; 
#define  KVASER_PCIEFD_PACK_TYPE_ACK 136 
#define  KVASER_PCIEFD_PACK_TYPE_ACK_DATA 135 
#define  KVASER_PCIEFD_PACK_TYPE_BUS_LOAD 134 
#define  KVASER_PCIEFD_PACK_TYPE_DATA 133 
#define  KVASER_PCIEFD_PACK_TYPE_EFLUSH_ACK 132 
#define  KVASER_PCIEFD_PACK_TYPE_EFRAME_ACK 131 
#define  KVASER_PCIEFD_PACK_TYPE_ERROR 130 
#define  KVASER_PCIEFD_PACK_TYPE_STATUS 129 
#define  KVASER_PCIEFD_PACK_TYPE_TXRQ 128 
 int KVASER_PCIEFD_RPACKET_DLC_SHIFT ; 
 int KVASER_PCIEFD_RPACKET_RTR ; 
 int can_dlc2len (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int kvaser_pciefd_handle_ack_packet (struct kvaser_pciefd*,struct kvaser_pciefd_rx_packet*) ; 
 int kvaser_pciefd_handle_data_packet (struct kvaser_pciefd*,struct kvaser_pciefd_rx_packet*,int /*<<< orphan*/ *) ; 
 int kvaser_pciefd_handle_eack_packet (struct kvaser_pciefd*,struct kvaser_pciefd_rx_packet*) ; 
 int kvaser_pciefd_handle_eflush_packet (struct kvaser_pciefd*,struct kvaser_pciefd_rx_packet*) ; 
 int kvaser_pciefd_handle_error_packet (struct kvaser_pciefd*,struct kvaser_pciefd_rx_packet*) ; 
 int kvaser_pciefd_handle_status_packet (struct kvaser_pciefd*,struct kvaser_pciefd_rx_packet*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int kvaser_pciefd_read_packet(struct kvaser_pciefd *pcie, int *start_pos,
				     int dma_buf)
{
	__le32 *buffer = pcie->dma_data[dma_buf];
	__le64 timestamp;
	struct kvaser_pciefd_rx_packet packet;
	struct kvaser_pciefd_rx_packet *p = &packet;
	u8 type;
	int pos = *start_pos;
	int size;
	int ret = 0;

	size = le32_to_cpu(buffer[pos++]);
	if (!size) {
		*start_pos = 0;
		return 0;
	}

	p->header[0] = le32_to_cpu(buffer[pos++]);
	p->header[1] = le32_to_cpu(buffer[pos++]);

	/* Read 64-bit timestamp */
	memcpy(&timestamp, &buffer[pos], sizeof(__le64));
	pos += 2;
	p->timestamp = le64_to_cpu(timestamp);

	type = (p->header[1] >> KVASER_PCIEFD_PACKET_TYPE_SHIFT) & 0xf;
	switch (type) {
	case KVASER_PCIEFD_PACK_TYPE_DATA:
		ret = kvaser_pciefd_handle_data_packet(pcie, p, &buffer[pos]);
		if (!(p->header[0] & KVASER_PCIEFD_RPACKET_RTR)) {
			u8 data_len;

			data_len = can_dlc2len(p->header[1] >>
					       KVASER_PCIEFD_RPACKET_DLC_SHIFT);
			pos += DIV_ROUND_UP(data_len, 4);
		}
		break;

	case KVASER_PCIEFD_PACK_TYPE_ACK:
		ret = kvaser_pciefd_handle_ack_packet(pcie, p);
		break;

	case KVASER_PCIEFD_PACK_TYPE_STATUS:
		ret = kvaser_pciefd_handle_status_packet(pcie, p);
		break;

	case KVASER_PCIEFD_PACK_TYPE_ERROR:
		ret = kvaser_pciefd_handle_error_packet(pcie, p);
		break;

	case KVASER_PCIEFD_PACK_TYPE_EFRAME_ACK:
		ret = kvaser_pciefd_handle_eack_packet(pcie, p);
		break;

	case KVASER_PCIEFD_PACK_TYPE_EFLUSH_ACK:
		ret = kvaser_pciefd_handle_eflush_packet(pcie, p);
		break;

	case KVASER_PCIEFD_PACK_TYPE_ACK_DATA:
	case KVASER_PCIEFD_PACK_TYPE_BUS_LOAD:
	case KVASER_PCIEFD_PACK_TYPE_TXRQ:
		dev_info(&pcie->pci->dev,
			 "Received unexpected packet type 0x%08X\n", type);
		break;

	default:
		dev_err(&pcie->pci->dev, "Unknown packet type 0x%08X\n", type);
		ret = -EIO;
		break;
	}

	if (ret)
		return ret;

	/* Position does not point to the end of the package,
	 * corrupted packet size?
	 */
	if ((*start_pos + size) != pos)
		return -EIO;

	/* Point to the next packet header, if any */
	*start_pos = pos;

	return ret;
}