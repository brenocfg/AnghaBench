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
struct sun4i_csi {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  v4l; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 

void sun4i_csi_dma_unregister(struct sun4i_csi *csi)
{
	v4l2_device_unregister(&csi->v4l);
	vb2_queue_release(&csi->queue);
	mutex_destroy(&csi->lock);
}