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
struct timer_list {int dummy; } ;
struct saa7134_dmaqueue {scalar_t__ curr; struct saa7134_dev* dev; } ;
struct saa7134_dev {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_REGION_ENABLE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  core_dbg (char*,scalar_t__) ; 
 struct saa7134_dmaqueue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct saa7134_dmaqueue* q ; 
 int /*<<< orphan*/  saa7134_buffer_finish (struct saa7134_dev*,struct saa7134_dmaqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7134_buffer_next (struct saa7134_dev*,struct saa7134_dmaqueue*) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timeout ; 

void saa7134_buffer_timeout(struct timer_list *t)
{
	struct saa7134_dmaqueue *q = from_timer(q, t, timeout);
	struct saa7134_dev *dev = q->dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->slock, flags);

	/* try to reset the hardware (SWRST) */
	saa_writeb(SAA7134_REGION_ENABLE, 0x00);
	saa_writeb(SAA7134_REGION_ENABLE, 0x80);
	saa_writeb(SAA7134_REGION_ENABLE, 0x00);

	/* flag current buffer as failed,
	   try to start over with the next one. */
	if (q->curr) {
		core_dbg("timeout on %p\n", q->curr);
		saa7134_buffer_finish(dev, q, VB2_BUF_STATE_ERROR);
	}
	saa7134_buffer_next(dev, q);
	spin_unlock_irqrestore(&dev->slock, flags);
}