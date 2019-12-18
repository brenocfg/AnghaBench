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
struct vpfe_fh {struct vpfe_device* vpfe_dev; } ;
struct vpfe_device {int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; int /*<<< orphan*/  v4l2_dev; } ;
struct videobuf_queue {struct vpfe_fh* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  state; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_QUEUED ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void vpfe_videobuf_queue(struct videobuf_queue *vq,
				struct videobuf_buffer *vb)
{
	/* Get the file handle object and device object */
	struct vpfe_fh *fh = vq->priv_data;
	struct vpfe_device *vpfe_dev = fh->vpfe_dev;
	unsigned long flags;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_buffer_queue\n");

	/* add the buffer to the DMA queue */
	spin_lock_irqsave(&vpfe_dev->dma_queue_lock, flags);
	list_add_tail(&vb->queue, &vpfe_dev->dma_queue);
	spin_unlock_irqrestore(&vpfe_dev->dma_queue_lock, flags);

	/* Change state of the buffer */
	vb->state = VIDEOBUF_QUEUED;
}