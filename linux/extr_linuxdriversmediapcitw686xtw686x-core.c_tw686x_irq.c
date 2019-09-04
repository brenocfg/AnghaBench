#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tw686x_dev {int /*<<< orphan*/  dma_delay_timer; int /*<<< orphan*/  lock; TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  INT_STATUS ; 
 int INT_STATUS_DMA_TOUT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PB_STATUS ; 
 int /*<<< orphan*/  TW686X_FIFO_ERROR (int) ; 
 int /*<<< orphan*/  VIDEO_FIFO_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int reg_read (struct tw686x_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tw686x_audio_irq (struct tw686x_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  tw686x_reset_channels (struct tw686x_dev*,unsigned int) ; 
 int /*<<< orphan*/  tw686x_video_irq (struct tw686x_dev*,unsigned int,int,int,unsigned int*) ; 

__attribute__((used)) static irqreturn_t tw686x_irq(int irq, void *dev_id)
{
	struct tw686x_dev *dev = (struct tw686x_dev *)dev_id;
	unsigned int video_requests, audio_requests, reset_ch;
	u32 fifo_status, fifo_signal, fifo_ov, fifo_bad, fifo_errors;
	u32 int_status, dma_en, video_en, pb_status;
	unsigned long flags;

	int_status = reg_read(dev, INT_STATUS); /* cleared on read */
	fifo_status = reg_read(dev, VIDEO_FIFO_STATUS);

	/* INT_STATUS does not include FIFO_STATUS errors! */
	if (!int_status && !TW686X_FIFO_ERROR(fifo_status))
		return IRQ_NONE;

	if (int_status & INT_STATUS_DMA_TOUT) {
		dev_dbg(&dev->pci_dev->dev,
			"DMA timeout. Resetting DMA for all channels\n");
		reset_ch = ~0;
		goto reset_channels;
	}

	spin_lock_irqsave(&dev->lock, flags);
	dma_en = reg_read(dev, DMA_CHANNEL_ENABLE);
	spin_unlock_irqrestore(&dev->lock, flags);

	video_en = dma_en & 0xff;
	fifo_signal = ~(fifo_status & 0xff) & video_en;
	fifo_ov = fifo_status >> 24;
	fifo_bad = fifo_status >> 16;

	/* Mask of channels with signal and FIFO errors */
	fifo_errors = fifo_signal & (fifo_ov | fifo_bad);

	reset_ch = 0;
	pb_status = reg_read(dev, PB_STATUS);

	/* Coalesce video frame/error events */
	video_requests = (int_status & video_en) | fifo_errors;
	audio_requests = (int_status & dma_en) >> 8;

	if (video_requests)
		tw686x_video_irq(dev, video_requests, pb_status,
				 fifo_status, &reset_ch);
	if (audio_requests)
		tw686x_audio_irq(dev, audio_requests, pb_status);

reset_channels:
	if (reset_ch) {
		spin_lock_irqsave(&dev->lock, flags);
		tw686x_reset_channels(dev, reset_ch);
		spin_unlock_irqrestore(&dev->lock, flags);
		mod_timer(&dev->dma_delay_timer,
			  jiffies + msecs_to_jiffies(100));
	}

	return IRQ_HANDLED;
}