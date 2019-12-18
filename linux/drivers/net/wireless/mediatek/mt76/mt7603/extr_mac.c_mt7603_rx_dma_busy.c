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
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int mt7603_rx_fifo_busy (struct mt7603_dev*) ; 
 int mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mt7603_rx_dma_busy(struct mt7603_dev *dev)
{
	if (!(mt76_rr(dev, MT_WPDMA_GLO_CFG) & MT_WPDMA_GLO_CFG_RX_DMA_BUSY))
		return false;

	return mt7603_rx_fifo_busy(dev);
}