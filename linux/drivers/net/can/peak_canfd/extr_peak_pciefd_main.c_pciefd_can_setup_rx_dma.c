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
typedef  scalar_t__ const u32 ;
struct pciefd_can {int rx_dma_laddr; } ;

/* Variables and functions */
 scalar_t__ const CANFD_CTL_RST_BIT ; 
 scalar_t__ const CANFD_CTL_UNC_BIT ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_CLR ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_CTL_SET ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_DMA_ADDR_H ; 
 int /*<<< orphan*/  PCIEFD_REG_CAN_RX_DMA_ADDR_L ; 
 int /*<<< orphan*/  pciefd_can_writereg (struct pciefd_can*,scalar_t__ const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciefd_can_setup_rx_dma(struct pciefd_can *priv)
{
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
	const u32 dma_addr_h = (u32)(priv->rx_dma_laddr >> 32);
#else
	const u32 dma_addr_h = 0;
#endif

	/* (DMA must be reset for Rx) */
	pciefd_can_writereg(priv, CANFD_CTL_RST_BIT, PCIEFD_REG_CAN_RX_CTL_SET);

	/* write the logical address of the Rx DMA area for this channel */
	pciefd_can_writereg(priv, (u32)priv->rx_dma_laddr,
			    PCIEFD_REG_CAN_RX_DMA_ADDR_L);
	pciefd_can_writereg(priv, dma_addr_h, PCIEFD_REG_CAN_RX_DMA_ADDR_H);

	/* also indicates that Rx DMA is cacheable */
	pciefd_can_writereg(priv, CANFD_CTL_UNC_BIT, PCIEFD_REG_CAN_RX_CTL_CLR);
}