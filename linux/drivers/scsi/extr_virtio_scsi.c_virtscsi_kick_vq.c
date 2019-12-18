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
struct virtio_scsi_vq {int /*<<< orphan*/  vq; int /*<<< orphan*/  vq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virtqueue_kick_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_notify (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtscsi_kick_vq(struct virtio_scsi_vq *vq)
{
	bool needs_kick;
	unsigned long flags;

	spin_lock_irqsave(&vq->vq_lock, flags);
	needs_kick = virtqueue_kick_prepare(vq->vq);
	spin_unlock_irqrestore(&vq->vq_lock, flags);

	if (needs_kick)
		virtqueue_notify(vq->vq);
}