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
struct vhost_scsi_inflight {int /*<<< orphan*/  comp; int /*<<< orphan*/  kref; } ;
struct vhost_scsi {int /*<<< orphan*/  vs_event_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  vs_completion_work; } ;

/* Variables and functions */
 int VHOST_SCSI_MAX_VQ ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_scsi_done_inflight ; 
 int /*<<< orphan*/  vhost_scsi_flush_vq (struct vhost_scsi*,int) ; 
 int /*<<< orphan*/  vhost_scsi_init_inflight (struct vhost_scsi*,struct vhost_scsi_inflight**) ; 
 int /*<<< orphan*/  vhost_work_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_scsi_flush(struct vhost_scsi *vs)
{
	struct vhost_scsi_inflight *old_inflight[VHOST_SCSI_MAX_VQ];
	int i;

	/* Init new inflight and remember the old inflight */
	vhost_scsi_init_inflight(vs, old_inflight);

	/*
	 * The inflight->kref was initialized to 1. We decrement it here to
	 * indicate the start of the flush operation so that it will reach 0
	 * when all the reqs are finished.
	 */
	for (i = 0; i < VHOST_SCSI_MAX_VQ; i++)
		kref_put(&old_inflight[i]->kref, vhost_scsi_done_inflight);

	/* Flush both the vhost poll and vhost work */
	for (i = 0; i < VHOST_SCSI_MAX_VQ; i++)
		vhost_scsi_flush_vq(vs, i);
	vhost_work_flush(&vs->dev, &vs->vs_completion_work);
	vhost_work_flush(&vs->dev, &vs->vs_event_work);

	/* Wait for all reqs issued before the flush to be finished */
	for (i = 0; i < VHOST_SCSI_MAX_VQ; i++)
		wait_for_completion(&old_inflight[i]->comp);
}