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
 int BIT (int) ; 
 scalar_t__ is_mt7628 (struct mt7603_dev*) ; 
 int mt7603_dma_debug (struct mt7603_dev*,int) ; 

__attribute__((used)) static bool mt7603_rx_fifo_busy(struct mt7603_dev *dev)
{
	if (is_mt7628(dev))
		return mt7603_dma_debug(dev, 9) & BIT(9);

	return mt7603_dma_debug(dev, 2) & BIT(8);
}