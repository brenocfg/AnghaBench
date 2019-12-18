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
struct vhost_virtqueue {scalar_t__ handle_kick; int /*<<< orphan*/  poll; int /*<<< orphan*/  mutex; struct vhost_dev* dev; int /*<<< orphan*/ * heads; int /*<<< orphan*/ * indirect; int /*<<< orphan*/ * log; } ;
struct vhost_dev {int nvqs; int iov_limit; int weight; int byte_weight; struct vhost_virtqueue** vqs; int /*<<< orphan*/  iotlb_lock; int /*<<< orphan*/  pending_list; int /*<<< orphan*/  read_list; int /*<<< orphan*/  wait; int /*<<< orphan*/  work_list; int /*<<< orphan*/ * worker; int /*<<< orphan*/ * mm; int /*<<< orphan*/ * iotlb; int /*<<< orphan*/ * umem; int /*<<< orphan*/ * log_ctx; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_poll_init (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct vhost_dev*) ; 
 int /*<<< orphan*/  vhost_vq_reset (struct vhost_dev*,struct vhost_virtqueue*) ; 

void vhost_dev_init(struct vhost_dev *dev,
		    struct vhost_virtqueue **vqs, int nvqs,
		    int iov_limit, int weight, int byte_weight)
{
	struct vhost_virtqueue *vq;
	int i;

	dev->vqs = vqs;
	dev->nvqs = nvqs;
	mutex_init(&dev->mutex);
	dev->log_ctx = NULL;
	dev->umem = NULL;
	dev->iotlb = NULL;
	dev->mm = NULL;
	dev->worker = NULL;
	dev->iov_limit = iov_limit;
	dev->weight = weight;
	dev->byte_weight = byte_weight;
	init_llist_head(&dev->work_list);
	init_waitqueue_head(&dev->wait);
	INIT_LIST_HEAD(&dev->read_list);
	INIT_LIST_HEAD(&dev->pending_list);
	spin_lock_init(&dev->iotlb_lock);


	for (i = 0; i < dev->nvqs; ++i) {
		vq = dev->vqs[i];
		vq->log = NULL;
		vq->indirect = NULL;
		vq->heads = NULL;
		vq->dev = dev;
		mutex_init(&vq->mutex);
		vhost_vq_reset(dev, vq);
		if (vq->handle_kick)
			vhost_poll_init(&vq->poll, vq->handle_kick,
					EPOLLIN, dev);
	}
}