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
typedef  int u32 ;
struct tw686x_dev {int pending_dma_en; int pending_dma_cmd; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int /*<<< orphan*/  DMA_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  DMA_CMD ; 
 int DMA_CMD_ENABLE ; 
 int reg_read (struct tw686x_dev*,int /*<<< orphan*/ ) ; 

void tw686x_enable_channel(struct tw686x_dev *dev, unsigned int channel)
{
	u32 dma_en = reg_read(dev, DMA_CHANNEL_ENABLE);
	u32 dma_cmd = reg_read(dev, DMA_CMD);

	dev->pending_dma_en |= dma_en | BIT(channel);
	dev->pending_dma_cmd |= dma_cmd | DMA_CMD_ENABLE | BIT(channel);
}