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
struct mt7601u_dev {int rxfilter; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_ENABLE_RX ; 
 int MT_MAC_SYS_CTRL_ENABLE_TX ; 
 int /*<<< orphan*/  MT_RX_FILTR_CFG ; 
 int MT_RX_FILTR_CFG_ACK ; 
 int MT_RX_FILTR_CFG_BA ; 
 int MT_RX_FILTR_CFG_CFACK ; 
 int MT_RX_FILTR_CFG_CFEND ; 
 int MT_RX_FILTR_CFG_CRC_ERR ; 
 int MT_RX_FILTR_CFG_CTRL_RSV ; 
 int MT_RX_FILTR_CFG_CTS ; 
 int MT_RX_FILTR_CFG_DUP ; 
 int MT_RX_FILTR_CFG_PHY_ERR ; 
 int MT_RX_FILTR_CFG_PROMISC ; 
 int MT_RX_FILTR_CFG_PSPOLL ; 
 int MT_RX_FILTR_CFG_RTS ; 
 int MT_RX_FILTR_CFG_VER_ERR ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll (struct mt7601u_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

int mt7601u_mac_start(struct mt7601u_dev *dev)
{
	mt7601u_wr(dev, MT_MAC_SYS_CTRL, MT_MAC_SYS_CTRL_ENABLE_TX);

	if (!mt76_poll(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		       MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 200000))
		return -ETIMEDOUT;

	dev->rxfilter = MT_RX_FILTR_CFG_CRC_ERR |
		MT_RX_FILTR_CFG_PHY_ERR | MT_RX_FILTR_CFG_PROMISC |
		MT_RX_FILTR_CFG_VER_ERR | MT_RX_FILTR_CFG_DUP |
		MT_RX_FILTR_CFG_CFACK | MT_RX_FILTR_CFG_CFEND |
		MT_RX_FILTR_CFG_ACK | MT_RX_FILTR_CFG_CTS |
		MT_RX_FILTR_CFG_RTS | MT_RX_FILTR_CFG_PSPOLL |
		MT_RX_FILTR_CFG_BA | MT_RX_FILTR_CFG_CTRL_RSV;
	mt7601u_wr(dev, MT_RX_FILTR_CFG, dev->rxfilter);

	mt7601u_wr(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_ENABLE_TX | MT_MAC_SYS_CTRL_ENABLE_RX);

	if (!mt76_poll(dev, MT_WPDMA_GLO_CFG, MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		       MT_WPDMA_GLO_CFG_RX_DMA_BUSY, 0, 50))
		return -ETIMEDOUT;

	return 0;
}