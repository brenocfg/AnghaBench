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
struct tw686x_dev {int /*<<< orphan*/  lock; scalar_t__ pending_dma_cmd; scalar_t__ pending_dma_en; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CHANNEL_ENABLE ; 
 int /*<<< orphan*/  DMA_CMD ; 
 struct tw686x_dev* dev ; 
 int /*<<< orphan*/  dma_delay_timer ; 
 struct tw686x_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct tw686x_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tw686x_dma_delay(struct timer_list *t)
{
	struct tw686x_dev *dev = from_timer(dev, t, dma_delay_timer);
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);

	reg_write(dev, DMA_CHANNEL_ENABLE, dev->pending_dma_en);
	reg_write(dev, DMA_CMD, dev->pending_dma_cmd);
	dev->pending_dma_en = 0;
	dev->pending_dma_cmd = 0;

	spin_unlock_irqrestore(&dev->lock, flags);
}