#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vhost_virtqueue {int /*<<< orphan*/  mutex; } ;
struct vhost_scsi_inflight {int /*<<< orphan*/  comp; int /*<<< orphan*/  kref; } ;
struct vhost_scsi {TYPE_1__* vqs; } ;
struct TYPE_2__ {int inflight_idx; struct vhost_scsi_inflight* inflights; struct vhost_virtqueue vq; } ;

/* Variables and functions */
 int VHOST_SCSI_MAX_VQ ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_scsi_init_inflight(struct vhost_scsi *vs,
				    struct vhost_scsi_inflight *old_inflight[])
{
	struct vhost_scsi_inflight *new_inflight;
	struct vhost_virtqueue *vq;
	int idx, i;

	for (i = 0; i < VHOST_SCSI_MAX_VQ; i++) {
		vq = &vs->vqs[i].vq;

		mutex_lock(&vq->mutex);

		/* store old infight */
		idx = vs->vqs[i].inflight_idx;
		if (old_inflight)
			old_inflight[i] = &vs->vqs[i].inflights[idx];

		/* setup new infight */
		vs->vqs[i].inflight_idx = idx ^ 1;
		new_inflight = &vs->vqs[i].inflights[idx ^ 1];
		kref_init(&new_inflight->kref);
		init_completion(&new_inflight->comp);

		mutex_unlock(&vq->mutex);
	}
}