#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {struct cx231xx_fh* priv_data; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  state; } ;
struct cx231xx_buffer {TYPE_4__ vb; } ;
struct TYPE_7__ {struct cx231xx_buffer* buf; } ;
struct TYPE_6__ {struct cx231xx_buffer* buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  slock; TYPE_2__ bulk_ctl; TYPE_1__ isoc_ctl; } ;
struct cx231xx {TYPE_3__ video_mode; scalar_t__ USE_ISO; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  videobuf_vmalloc_free (TYPE_4__*) ; 
 int /*<<< orphan*/  videobuf_waiton (struct videobuf_queue*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_buffer(struct videobuf_queue *vq, struct cx231xx_buffer *buf)
{
	struct cx231xx_fh *fh = vq->priv_data;
	struct cx231xx *dev = fh->dev;
	unsigned long flags = 0;

	BUG_ON(in_interrupt());

	spin_lock_irqsave(&dev->video_mode.slock, flags);
	if (dev->USE_ISO) {
		if (dev->video_mode.isoc_ctl.buf == buf)
			dev->video_mode.isoc_ctl.buf = NULL;
	} else {
		if (dev->video_mode.bulk_ctl.buf == buf)
			dev->video_mode.bulk_ctl.buf = NULL;
	}
	spin_unlock_irqrestore(&dev->video_mode.slock, flags);
	videobuf_waiton(vq, &buf->vb, 0, 0);
	videobuf_vmalloc_free(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}