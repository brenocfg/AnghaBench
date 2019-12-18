#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {unsigned int index; TYPE_3__* vdev; struct virtio_ccw_vq_info* priv; } ;
struct virtio_ccw_vq_info {TYPE_4__* info_block; int /*<<< orphan*/  node; } ;
struct virtio_ccw_device {scalar_t__ revision; int /*<<< orphan*/  cdev; int /*<<< orphan*/  lock; } ;
struct ccw1 {int count; scalar_t__ cda; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_6__ {unsigned int index; scalar_t__ used; scalar_t__ avail; scalar_t__ num; scalar_t__ desc; } ;
struct TYPE_5__ {unsigned int index; scalar_t__ num; scalar_t__ align; scalar_t__ queue; } ;
struct TYPE_8__ {TYPE_2__ s; TYPE_1__ l; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_SET_VQ ; 
 int ENODEV ; 
 unsigned int VIRTIO_CCW_DOING_SET_VQ ; 
 int /*<<< orphan*/  ccw_device_dma_free (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct virtio_ccw_vq_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virtio_ccw_device* to_vc_device (TYPE_3__*) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 

__attribute__((used)) static void virtio_ccw_del_vq(struct virtqueue *vq, struct ccw1 *ccw)
{
	struct virtio_ccw_device *vcdev = to_vc_device(vq->vdev);
	struct virtio_ccw_vq_info *info = vq->priv;
	unsigned long flags;
	int ret;
	unsigned int index = vq->index;

	/* Remove from our list. */
	spin_lock_irqsave(&vcdev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vcdev->lock, flags);

	/* Release from host. */
	if (vcdev->revision == 0) {
		info->info_block->l.queue = 0;
		info->info_block->l.align = 0;
		info->info_block->l.index = index;
		info->info_block->l.num = 0;
		ccw->count = sizeof(info->info_block->l);
	} else {
		info->info_block->s.desc = 0;
		info->info_block->s.index = index;
		info->info_block->s.num = 0;
		info->info_block->s.avail = 0;
		info->info_block->s.used = 0;
		ccw->count = sizeof(info->info_block->s);
	}
	ccw->cmd_code = CCW_CMD_SET_VQ;
	ccw->flags = 0;
	ccw->cda = (__u32)(unsigned long)(info->info_block);
	ret = ccw_io_helper(vcdev, ccw,
			    VIRTIO_CCW_DOING_SET_VQ | index);
	/*
	 * -ENODEV isn't considered an error: The device is gone anyway.
	 * This may happen on device detach.
	 */
	if (ret && (ret != -ENODEV))
		dev_warn(&vq->vdev->dev, "Error %d while deleting queue %d\n",
			 ret, index);

	vring_del_virtqueue(vq);
	ccw_device_dma_free(vcdev->cdev, info->info_block,
			    sizeof(*info->info_block));
	kfree(info);
}