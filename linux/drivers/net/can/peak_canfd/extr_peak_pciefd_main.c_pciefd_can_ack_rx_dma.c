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
struct pciefd_can {int irq_tag; scalar_t__ rx_dma_vaddr; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_ACK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciefd_can_ack_rx_dma(struct pciefd_can *priv)
{
	/* read value of current IRQ tag and inc it for next one */
	priv->irq_tag = le32_to_cpu(*(__le32 *)priv->rx_dma_vaddr);
	priv->irq_tag++;
	priv->irq_tag &= 0xf;

	/* write the next IRQ tag for this CAN */
	pciefd_can_writereg(priv, priv->irq_tag, PCIEFD_REG_CAN_RX_CTL_ACK);
}