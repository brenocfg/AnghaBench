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
struct r592_device {int dma_capable; } ;

/* Variables and functions */
 int /*<<< orphan*/  R592_FIFO_DMA_SETTINGS ; 
 int R592_FIFO_DMA_SETTINGS_CAP ; 
 scalar_t__ r592_enable_dma ; 
 int r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_check_dma(struct r592_device *dev)
{
	dev->dma_capable = r592_enable_dma &&
		(r592_read_reg(dev, R592_FIFO_DMA_SETTINGS) &
			R592_FIFO_DMA_SETTINGS_CAP);
}