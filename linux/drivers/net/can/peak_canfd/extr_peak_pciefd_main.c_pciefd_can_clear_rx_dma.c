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
struct pciefd_can {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_CTL_RST_BIT ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_SET ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_DMA_ADDR_H ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_DMA_ADDR_L ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciefd_can_clear_rx_dma(struct pciefd_can *priv)
{
	/* DMA must be reset for Rx */
	pciefd_can_writereg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_RX_CTL_SET);

	/* clear the logical address of the Rx DMA area for this channel */
	pciefd_can_writereg(priv, 0, PCIEFD_REG_CAN_RX_DMA_ADDR_L);
	pciefd_can_writereg(priv, 0, PCIEFD_REG_CAN_RX_DMA_ADDR_H);
}