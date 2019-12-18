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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  unregister_work; int /*<<< orphan*/  adap; } ;
struct drm_dp_aux {TYPE_1__ cec; int /*<<< orphan*/  transfer; } ;

/* Variables and functions */
 int HZ ; 
 int NEVER_UNREG_DELAY ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_phys_addr_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_cec_cap (struct drm_dp_aux*,int /*<<< orphan*/ *) ; 
 int drm_dp_cec_unregister_delay ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

void drm_dp_cec_unset_edid(struct drm_dp_aux *aux)
{
	/* No transfer function was set, so not a DP connector */
	if (!aux->transfer)
		return;

	cancel_delayed_work_sync(&aux->cec.unregister_work);

	mutex_lock(&aux->cec.lock);
	if (!aux->cec.adap)
		goto unlock;

	cec_phys_addr_invalidate(aux->cec.adap);
	/*
	 * We're done if we want to keep the CEC device
	 * (drm_dp_cec_unregister_delay is >= NEVER_UNREG_DELAY) or if the
	 * DPCD still indicates the CEC capability (expected for an integrated
	 * HDMI branch device).
	 */
	if (drm_dp_cec_unregister_delay < NEVER_UNREG_DELAY &&
	    !drm_dp_cec_cap(aux, NULL)) {
		/*
		 * Unregister the CEC adapter after drm_dp_cec_unregister_delay
		 * seconds. This to debounce short HPD off-and-on cycles from
		 * displays.
		 */
		schedule_delayed_work(&aux->cec.unregister_work,
				      drm_dp_cec_unregister_delay * HZ);
	}
unlock:
	mutex_unlock(&aux->cec.lock);
}