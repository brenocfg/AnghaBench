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
struct saa7146_dmaqueue {scalar_t__ curr; struct saa7146_dev* dev; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*,scalar_t__) ; 
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_dev*,struct saa7146_dmaqueue*) ; 
 int /*<<< orphan*/  VIDEOBUF_ERROR ; 
 struct saa7146_dmaqueue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct saa7146_dmaqueue* q ; 
 int /*<<< orphan*/  saa7146_buffer_finish (struct saa7146_dev*,struct saa7146_dmaqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timeout ; 

void saa7146_buffer_timeout(struct timer_list *t)
{
	struct saa7146_dmaqueue *q = from_timer(q, t, timeout);
	struct saa7146_dev *dev = q->dev;
	unsigned long flags;

	DEB_EE("dev:%p, dmaq:%p\n", dev, q);

	spin_lock_irqsave(&dev->slock,flags);
	if (q->curr) {
		DEB_D("timeout on %p\n", q->curr);
		saa7146_buffer_finish(dev,q,VIDEOBUF_ERROR);
	}

	/* we don't restart the transfer here like other drivers do. when
	   a streaming capture is disabled, the timeout function will be
	   called for the current buffer. if we activate the next buffer now,
	   we mess up our capture logic. if a timeout occurs on another buffer,
	   then something is seriously broken before, so no need to buffer the
	   next capture IMHO... */
/*
	saa7146_buffer_next(dev,q);
*/
	spin_unlock_irqrestore(&dev->slock,flags);
}