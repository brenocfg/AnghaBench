#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
struct kvaser_pciefd_rx_packet {int* header; } ;
struct kvaser_pciefd_can {int /*<<< orphan*/  flush_comp; } ;
struct kvaser_pciefd {size_t nr_channels; struct kvaser_pciefd_can** can; } ;

/* Variables and functions */
 int EIO ; 
 int KVASER_PCIEFD_PACKET_CHID_SHIFT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kvaser_pciefd_handle_eflush_packet(struct kvaser_pciefd *pcie,
					      struct kvaser_pciefd_rx_packet *p)
{
	struct kvaser_pciefd_can *can;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	if (ch_id >= pcie->nr_channels)
		return -EIO;

	can = pcie->can[ch_id];

	if (!completion_done(&can->flush_comp))
		complete(&can->flush_comp);

	return 0;
}