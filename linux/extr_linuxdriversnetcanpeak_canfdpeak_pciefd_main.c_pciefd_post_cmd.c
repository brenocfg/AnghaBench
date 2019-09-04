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
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct peak_canfd_priv {TYPE_3__ can; } ;
struct TYPE_5__ {TYPE_1__* ndev; } ;
struct pciefd_can {TYPE_2__ ucan; int /*<<< orphan*/  board; int /*<<< orphan*/  pucan_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_CTL_IEN_BIT ; 
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_CLR ; 
 int /*<<< orphan*/  PCIEFD_REG_SYS_VER1 ; 
#define  PUCAN_CMD_RESET_MODE 128 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pciefd_can*) ; 
 int /*<<< orphan*/  pciefd_can_clear_rx_dma (struct pciefd_can*) ; 
 int /*<<< orphan*/  pciefd_can_clear_tx_dma (struct pciefd_can*) ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_sys_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pucan_cmd_get_opcode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pciefd_post_cmd(struct peak_canfd_priv *ucan)
{
	struct pciefd_can *priv = (struct pciefd_can *)ucan;
	u16 cmd = pucan_cmd_get_opcode(&priv->pucan_cmd);

	switch (cmd) {
	case PUCAN_CMD_RESET_MODE:

		if (ucan->can.state == CAN_STATE_STOPPED)
			break;

		/* controller now in reset mode: */

		/* disable IRQ for this CAN */
		pciefd_can_writereg(priv, CANFD_CTL_IEN_BIT,
				    PCIEFD_REG_CAN_RX_CTL_CLR);

		/* stop and reset DMA addresses in Tx/Rx engines */
		pciefd_can_clear_tx_dma(priv);
		pciefd_can_clear_rx_dma(priv);

		/* wait for above commands to complete (read cycle) */
		(void)pciefd_sys_readreg(priv->board, PCIEFD_REG_SYS_VER1);

		free_irq(priv->ucan.ndev->irq, priv);

		ucan->can.state = CAN_STATE_STOPPED;

		break;
	}

	return 0;
}