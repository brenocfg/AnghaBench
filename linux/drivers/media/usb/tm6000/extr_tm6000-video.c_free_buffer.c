#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {struct tm6000_fh* priv_data; } ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct TYPE_3__ {struct tm6000_buffer* buf; } ;
struct tm6000_core {int /*<<< orphan*/  slock; TYPE_1__ isoc_ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct tm6000_buffer {TYPE_2__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIDEOBUF_NEEDS_INIT ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  videobuf_vmalloc_free (TYPE_2__*) ; 

__attribute__((used)) static void free_buffer(struct videobuf_queue *vq, struct tm6000_buffer *buf)
{
	struct tm6000_fh *fh = vq->priv_data;
	struct tm6000_core   *dev = fh->dev;
	unsigned long flags;

	BUG_ON(in_interrupt());

	/* We used to wait for the buffer to finish here, but this didn't work
	   because, as we were keeping the state as VIDEOBUF_QUEUED,
	   videobuf_queue_cancel marked it as finished for us.
	   (Also, it could wedge forever if the hardware was misconfigured.)

	   This should be safe; by the time we get here, the buffer isn't
	   queued anymore. If we ever start marking the buffers as
	   VIDEOBUF_ACTIVE, it won't be, though.
	*/
	spin_lock_irqsave(&dev->slock, flags);
	if (dev->isoc_ctl.buf == buf)
		dev->isoc_ctl.buf = NULL;
	spin_unlock_irqrestore(&dev->slock, flags);

	videobuf_vmalloc_free(&buf->vb);
	buf->vb.state = VIDEOBUF_NEEDS_INIT;
}