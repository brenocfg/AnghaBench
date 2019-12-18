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
struct vhost_virtqueue {int /*<<< orphan*/  poll; struct vhost_dev* dev; } ;
struct vhost_dev {int byte_weight; int weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_poll_queue (int /*<<< orphan*/ *) ; 

bool vhost_exceeds_weight(struct vhost_virtqueue *vq,
			  int pkts, int total_len)
{
	struct vhost_dev *dev = vq->dev;

	if ((dev->byte_weight && total_len >= dev->byte_weight) ||
	    pkts >= dev->weight) {
		vhost_poll_queue(&vq->poll);
		return true;
	}

	return false;
}