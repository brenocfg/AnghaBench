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
struct drm_self_refresh_data {int /*<<< orphan*/  exit_avg_ms; int /*<<< orphan*/  entry_avg_ms; int /*<<< orphan*/  avg_mutex; struct drm_crtc* crtc; int /*<<< orphan*/  entry_work; } ;
struct drm_crtc {struct drm_self_refresh_data* self_refresh_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SELF_REFRESH_AVG_SEED_MS ; 
 scalar_t__ WARN_ON (struct drm_self_refresh_data*) ; 
 int /*<<< orphan*/  drm_self_refresh_helper_entry_work ; 
 int /*<<< orphan*/  ewma_psr_time_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewma_psr_time_init (int /*<<< orphan*/ *) ; 
 struct drm_self_refresh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int drm_self_refresh_helper_init(struct drm_crtc *crtc)
{
	struct drm_self_refresh_data *sr_data = crtc->self_refresh_data;

	/* Helper is already initialized */
	if (WARN_ON(sr_data))
		return -EINVAL;

	sr_data = kzalloc(sizeof(*sr_data), GFP_KERNEL);
	if (!sr_data)
		return -ENOMEM;

	INIT_DELAYED_WORK(&sr_data->entry_work,
			  drm_self_refresh_helper_entry_work);
	sr_data->crtc = crtc;
	mutex_init(&sr_data->avg_mutex);
	ewma_psr_time_init(&sr_data->entry_avg_ms);
	ewma_psr_time_init(&sr_data->exit_avg_ms);

	/*
	 * Seed the averages so they're non-zero (and sufficiently large
	 * for even poorly performing panels). As time goes on, this will be
	 * averaged out and the values will trend to their true value.
	 */
	ewma_psr_time_add(&sr_data->entry_avg_ms, SELF_REFRESH_AVG_SEED_MS);
	ewma_psr_time_add(&sr_data->exit_avg_ms, SELF_REFRESH_AVG_SEED_MS);

	crtc->self_refresh_data = sr_data;
	return 0;
}