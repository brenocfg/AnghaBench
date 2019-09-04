#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xen_drm_front_drm_pipeline {int /*<<< orphan*/  pflip_to_worker; } ;
struct xen_drm_front_drm_info {struct xen_drm_front_drm_pipeline* pipeline; TYPE_2__* front_info; } ;
struct TYPE_3__ {int num_connectors; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_pending_event (struct xen_drm_front_drm_pipeline*) ; 

void xen_drm_front_kms_fini(struct xen_drm_front_drm_info *drm_info)
{
	int i;

	for (i = 0; i < drm_info->front_info->cfg.num_connectors; i++) {
		struct xen_drm_front_drm_pipeline *pipeline =
				&drm_info->pipeline[i];

		cancel_delayed_work_sync(&pipeline->pflip_to_worker);

		send_pending_event(pipeline);
	}
}