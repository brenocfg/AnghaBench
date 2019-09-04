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
struct videobuf_queue {struct omap_vout_device* priv_data; } ;
struct videobuf_buffer {int /*<<< orphan*/  state; int /*<<< orphan*/  queue; } ;
struct omap_vout_device {int /*<<< orphan*/  dma_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEOBUF_QUEUED ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_vout_buffer_queue(struct videobuf_queue *q,
			  struct videobuf_buffer *vb)
{
	struct omap_vout_device *vout = q->priv_data;

	/* Driver is also maintainig a queue. So enqueue buffer in the driver
	 * queue */
	list_add_tail(&vb->queue, &vout->dma_queue);

	vb->state = VIDEOBUF_QUEUED;
}