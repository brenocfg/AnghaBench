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
struct vhost_virtqueue {int /*<<< orphan*/  poll; } ;
struct vhost_net {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_disable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_enable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_poll_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_vq_avail_empty (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 

__attribute__((used)) static void vhost_net_busy_poll_try_queue(struct vhost_net *net,
					  struct vhost_virtqueue *vq)
{
	if (!vhost_vq_avail_empty(&net->dev, vq)) {
		vhost_poll_queue(&vq->poll);
	} else if (unlikely(vhost_enable_notify(&net->dev, vq))) {
		vhost_disable_notify(&net->dev, vq);
		vhost_poll_queue(&vq->poll);
	}
}