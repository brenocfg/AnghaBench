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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int MT_INT_RX_DONE_ALL ; 
 int MT_INT_TX_DONE_ALL ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG_DMA_BURST_SIZE ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE ; 
 int /*<<< orphan*/  mt7603_irq_enable (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt7603_mac_start (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_for_wpdma (struct mt7603_dev*) ; 

void mt7603_mac_dma_start(struct mt7603_dev *dev)
{
	mt7603_mac_start(dev);

	wait_for_wpdma(dev);
	usleep_range(50, 100);

	mt76_set(dev, MT_WPDMA_GLO_CFG,
		 (MT_WPDMA_GLO_CFG_TX_DMA_EN |
		  MT_WPDMA_GLO_CFG_RX_DMA_EN |
		  FIELD_PREP(MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 3) |
		  MT_WPDMA_GLO_CFG_TX_WRITEBACK_DONE));

	mt7603_irq_enable(dev, MT_INT_RX_DONE_ALL | MT_INT_TX_DONE_ALL);
}