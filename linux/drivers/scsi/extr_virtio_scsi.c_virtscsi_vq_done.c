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
struct virtqueue {int dummy; } ;
struct virtio_scsi_vq {int /*<<< orphan*/  vq_lock; struct virtqueue* vq; } ;
struct virtio_scsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 
 int /*<<< orphan*/  virtqueue_enable_cb (struct virtqueue*) ; 
 void* virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_is_broken (struct virtqueue*) ; 

__attribute__((used)) static void virtscsi_vq_done(struct virtio_scsi *vscsi,
			     struct virtio_scsi_vq *virtscsi_vq,
			     void (*fn)(struct virtio_scsi *vscsi, void *buf))
{
	void *buf;
	unsigned int len;
	unsigned long flags;
	struct virtqueue *vq = virtscsi_vq->vq;

	spin_lock_irqsave(&virtscsi_vq->vq_lock, flags);
	do {
		virtqueue_disable_cb(vq);
		while ((buf = virtqueue_get_buf(vq, &len)) != NULL)
			fn(vscsi, buf);

		if (unlikely(virtqueue_is_broken(vq)))
			break;
	} while (!virtqueue_enable_cb(vq));
	spin_unlock_irqrestore(&virtscsi_vq->vq_lock, flags);
}