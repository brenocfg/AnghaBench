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
struct drm_self_refresh_data {int /*<<< orphan*/  entry_work; } ;
struct drm_crtc {struct drm_self_refresh_data* self_refresh_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_self_refresh_data*) ; 

void drm_self_refresh_helper_cleanup(struct drm_crtc *crtc)
{
	struct drm_self_refresh_data *sr_data = crtc->self_refresh_data;

	/* Helper is already uninitialized */
	if (!sr_data)
		return;

	crtc->self_refresh_data = NULL;

	cancel_delayed_work_sync(&sr_data->entry_work);
	kfree(sr_data);
}