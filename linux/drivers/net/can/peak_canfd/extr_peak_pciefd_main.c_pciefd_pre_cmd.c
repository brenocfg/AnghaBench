#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  state; } ;
struct peak_canfd_priv {TYPE_2__ can; } ;
struct TYPE_4__ {TYPE_3__* ndev; } ;
struct pciefd_can {TYPE_1__ ucan; int /*<<< orphan*/  pucan_cmd; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CANFD_CTL_IEN_BIT ; 
 int CANFD_CTL_IRQ_CL_DEF ; 
 int CANFD_CTL_IRQ_TL_DEF ; 
 int CANFD_CTL_RST_BIT ; 
 int /*<<< orphan*/  CANFD_MISC_TS_RST ; 
 int /*<<< orphan*/  CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCIEFD_DRV_NAME ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_MISC ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_CLR ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_SET ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_WRT ; 
#define  PUCAN_CMD_LISTEN_ONLY_MODE 129 
#define  PUCAN_CMD_NORMAL_MODE 128 
 int /*<<< orphan*/  pciefd_can_ack_rx_dma (struct pciefd_can*) ; 
 int /*<<< orphan*/  pciefd_can_setup_rx_dma (struct pciefd_can*) ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_irq_handler ; 
 int pucan_cmd_get_opcode (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pciefd_can*) ; 

__attribute__((used)) static int pciefd_pre_cmd(struct peak_canfd_priv *ucan)
{
	struct pciefd_can *priv = (struct pciefd_can *)ucan;
	u16 cmd = pucan_cmd_get_opcode(&priv->pucan_cmd);
	int err;

	/* pre-process command */
	switch (cmd) {
	case PUCAN_CMD_NORMAL_MODE:
	case PUCAN_CMD_LISTEN_ONLY_MODE:

		if (ucan->can.state == CAN_STATE_BUS_OFF)
			break;

		/* going into operational mode: setup IRQ handler */
		err = request_irq(priv->ucan.ndev->irq,
				  pciefd_irq_handler,
				  IRQF_SHARED,
				  PCIEFD_DRV_NAME,
				  priv);
		if (err)
			return err;

		/* setup Rx DMA address */
		pciefd_can_setup_rx_dma(priv);

		/* setup max count of msgs per IRQ */
		pciefd_can_writereg(priv, (CANFD_CTL_IRQ_TL_DEF) << 8 |
				    CANFD_CTL_IRQ_CL_DEF,
				    PCIEFD_REG_CAN_RX_CTL_WRT);

		/* clear DMA RST for Rx (Rx start) */
		pciefd_can_writereg(priv, CANFD_CTL_RST_BIT,
				    PCIEFD_REG_CAN_RX_CTL_CLR);

		/* reset timestamps */
		pciefd_can_writereg(priv, !CANFD_MISC_TS_RST,
				    PCIEFD_REG_CAN_MISC);

		/* do an initial ACK */
		pciefd_can_ack_rx_dma(priv);

		/* enable IRQ for this CAN after having set next irq_tag */
		pciefd_can_writereg(priv, CANFD_CTL_IEN_BIT,
				    PCIEFD_REG_CAN_RX_CTL_SET);

		/* Tx path will be setup as soon as RX_BARRIER is received */
		break;
	default:
		break;
	}

	return 0;
}