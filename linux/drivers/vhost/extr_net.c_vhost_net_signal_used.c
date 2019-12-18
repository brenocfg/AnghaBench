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
struct vhost_virtqueue {int /*<<< orphan*/  heads; struct vhost_dev* dev; } ;
struct vhost_net_virtqueue {int /*<<< orphan*/  done_idx; struct vhost_virtqueue vq; } ;
struct vhost_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_add_used_and_signal_n (struct vhost_dev*,struct vhost_virtqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vhost_net_signal_used(struct vhost_net_virtqueue *nvq)
{
	struct vhost_virtqueue *vq = &nvq->vq;
	struct vhost_dev *dev = vq->dev;

	if (!nvq->done_idx)
		return;

	vhost_add_used_and_signal_n(dev, vq, vq->heads, nvq->done_idx);
	nvq->done_idx = 0;
}