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
struct tw686x_dev {int /*<<< orphan*/ * snd_card; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  DMA_CMD ; 
 int reg_read (struct tw686x_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct tw686x_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void tw686x_audio_free(struct tw686x_dev *dev)
{
	unsigned long flags;
	u32 dma_ch_mask;
	u32 dma_cmd;

	spin_lock_irqsave(&dev->lock, flags);
	dma_cmd = reg_read(dev, DMA_CMD);
	dma_ch_mask = reg_read(dev, DMA_CHANNEL_ENABLE);
	reg_write(dev, DMA_CMD, dma_cmd & ~0xff00);
	reg_write(dev, DMA_CHANNEL_ENABLE, dma_ch_mask & ~0xff00);
	spin_unlock_irqrestore(&dev->lock, flags);

	if (!dev->snd_card)
		return;
	snd_card_free(dev->snd_card);
	dev->snd_card = NULL;
}