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
typedef  int /*<<< orphan*/  u64 ;
struct xen_drm_front_drm_pipeline {int /*<<< orphan*/  pflip_to_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_pending_event (struct xen_drm_front_drm_pipeline*) ; 

void xen_drm_front_kms_on_frame_done(struct xen_drm_front_drm_pipeline *pipeline,
				     u64 fb_cookie)
{
	/*
	 * This runs in interrupt context, e.g. under
	 * drm_info->front_info->io_lock, so we cannot call _sync version
	 * to cancel the work
	 */
	cancel_delayed_work(&pipeline->pflip_to_worker);

	send_pending_event(pipeline);
}