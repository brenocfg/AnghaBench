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
typedef  size_t u8 ;
typedef  int u32 ;
struct kvaser_pciefd_rx_packet {int* header; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct kvaser_pciefd_can {int cmd_seq; int /*<<< orphan*/  start_comp; int /*<<< orphan*/  bec_poll_timer; TYPE_1__ can; scalar_t__ reg_base; } ;
struct kvaser_pciefd {size_t nr_channels; struct kvaser_pciefd_can** can; } ;

/* Variables and functions */
 scalar_t__ CAN_STATE_BUS_OFF ; 
 scalar_t__ CAN_STATE_ERROR_ACTIVE ; 
 int EIO ; 
 int /*<<< orphan*/  KVASER_PCIEFD_BEC_POLL_FREQ ; 
 int KVASER_PCIEFD_KCAN_CMD_AT ; 
 scalar_t__ KVASER_PCIEFD_KCAN_CMD_REG ; 
 int KVASER_PCIEFD_KCAN_CMD_SEQ_SHIFT ; 
 int KVASER_PCIEFD_KCAN_CTRL_EFLUSH ; 
 scalar_t__ KVASER_PCIEFD_KCAN_CTRL_REG ; 
 scalar_t__ KVASER_PCIEFD_KCAN_IEN_REG ; 
 int KVASER_PCIEFD_KCAN_IRQ_ABD ; 
 scalar_t__ KVASER_PCIEFD_KCAN_IRQ_REG ; 
 int KVASER_PCIEFD_KCAN_IRQ_TFD ; 
 int KVASER_PCIEFD_KCAN_STAT_BUS_OFF_MSK ; 
 int KVASER_PCIEFD_KCAN_STAT_IDLE ; 
 scalar_t__ KVASER_PCIEFD_KCAN_STAT_REG ; 
 int KVASER_PCIEFD_KCAN_STAT_SEQNO_SHIFT ; 
 scalar_t__ KVASER_PCIEFD_KCAN_TX_NPACKETS_REG ; 
 int KVASER_PCIEFD_PACKET_CHID_SHIFT ; 
 size_t KVASER_PCIEFD_PACKET_SEQ_MSK ; 
 int KVASER_PCIEFD_SPACK_AUTO ; 
 int KVASER_PCIEFD_SPACK_IDET ; 
 int KVASER_PCIEFD_SPACK_IRM ; 
 int KVASER_PCIEFD_SPACK_RMCD ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_handle_status_resp (struct kvaser_pciefd_can*,struct kvaser_pciefd_rx_packet*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_pciefd_handle_status_packet(struct kvaser_pciefd *pcie,
					      struct kvaser_pciefd_rx_packet *p)
{
	struct kvaser_pciefd_can *can;
	u8 cmdseq;
	u32 status;
	u8 ch_id = (p->header[1] >> KVASER_PCIEFD_PACKET_CHID_SHIFT) & 0x7;

	if (ch_id >= pcie->nr_channels)
		return -EIO;

	can = pcie->can[ch_id];

	status = ioread32(can->reg_base + KVASER_PCIEFD_KCAN_STAT_REG);
	cmdseq = (status >> KVASER_PCIEFD_KCAN_STAT_SEQNO_SHIFT) & 0xff;

	/* Reset done, start abort and flush */
	if (p->header[0] & KVASER_PCIEFD_SPACK_IRM &&
	    p->header[0] & KVASER_PCIEFD_SPACK_RMCD &&
	    p->header[1] & KVASER_PCIEFD_SPACK_AUTO &&
	    cmdseq == (p->header[1] & KVASER_PCIEFD_PACKET_SEQ_MSK) &&
	    status & KVASER_PCIEFD_KCAN_STAT_IDLE) {
		u32 cmd;

		iowrite32(KVASER_PCIEFD_KCAN_IRQ_ABD,
			  can->reg_base + KVASER_PCIEFD_KCAN_IRQ_REG);
		cmd = KVASER_PCIEFD_KCAN_CMD_AT;
		cmd |= ++can->cmd_seq << KVASER_PCIEFD_KCAN_CMD_SEQ_SHIFT;
		iowrite32(cmd, can->reg_base + KVASER_PCIEFD_KCAN_CMD_REG);

		iowrite32(KVASER_PCIEFD_KCAN_IRQ_TFD,
			  can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
	} else if (p->header[0] & KVASER_PCIEFD_SPACK_IDET &&
		   p->header[0] & KVASER_PCIEFD_SPACK_IRM &&
		   cmdseq == (p->header[1] & KVASER_PCIEFD_PACKET_SEQ_MSK) &&
		   status & KVASER_PCIEFD_KCAN_STAT_IDLE) {
		/* Reset detected, send end of flush if no packet are in FIFO */
		u8 count = ioread32(can->reg_base +
				    KVASER_PCIEFD_KCAN_TX_NPACKETS_REG) & 0xff;

		if (!count)
			iowrite32(KVASER_PCIEFD_KCAN_CTRL_EFLUSH,
				  can->reg_base + KVASER_PCIEFD_KCAN_CTRL_REG);
	} else if (!(p->header[1] & KVASER_PCIEFD_SPACK_AUTO) &&
		   cmdseq == (p->header[1] & KVASER_PCIEFD_PACKET_SEQ_MSK)) {
		/* Response to status request received */
		kvaser_pciefd_handle_status_resp(can, p);
		if (can->can.state != CAN_STATE_BUS_OFF &&
		    can->can.state != CAN_STATE_ERROR_ACTIVE) {
			mod_timer(&can->bec_poll_timer,
				  KVASER_PCIEFD_BEC_POLL_FREQ);
		}
	} else if (p->header[0] & KVASER_PCIEFD_SPACK_RMCD &&
		   !(status & KVASER_PCIEFD_KCAN_STAT_BUS_OFF_MSK)) {
		/* Reset to bus on detected */
		if (!completion_done(&can->start_comp))
			complete(&can->start_comp);
	}

	return 0;
}