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
struct wil6210_vif {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rejected_by_host; } ;
struct TYPE_3__ {int /*<<< orphan*/  suspend; } ;
struct wil6210_priv {scalar_t__ recovery_state; TYPE_2__ suspend_stats; int /*<<< orphan*/  vif_mutex; struct wil6210_vif** vifs; int /*<<< orphan*/  status; TYPE_1__ platform_ops; int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int EBUSY ; 
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  WMI_FW_CAPABILITY_WMI_ONLY ; 
 scalar_t__ debug_fw ; 
 scalar_t__ fw_recovery_idle ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_can_suspend_vif (struct wil6210_priv*,struct wil6210_vif*,int) ; 
 int /*<<< orphan*/  wil_dbg_pm (struct wil6210_priv*,char*,...) ; 
 int wil_has_active_ifaces (struct wil6210_priv*,int,int) ; 
 int /*<<< orphan*/  wil_status_resetting ; 

int wil_can_suspend(struct wil6210_priv *wil, bool is_runtime)
{
	int rc = 0, i;
	bool wmi_only = test_bit(WMI_FW_CAPABILITY_WMI_ONLY,
				 wil->fw_capabilities);
	bool active_ifaces;

	wil_dbg_pm(wil, "can_suspend: %s\n", is_runtime ? "runtime" : "system");

	if (wmi_only || debug_fw) {
		wil_dbg_pm(wil, "Deny any suspend - %s mode\n",
			   wmi_only ? "wmi_only" : "debug_fw");
		rc = -EBUSY;
		goto out;
	}
	if (is_runtime && !wil->platform_ops.suspend) {
		rc = -EBUSY;
		goto out;
	}

	mutex_lock(&wil->vif_mutex);
	active_ifaces = wil_has_active_ifaces(wil, true, false);
	mutex_unlock(&wil->vif_mutex);

	if (!active_ifaces) {
		/* can always sleep when down */
		wil_dbg_pm(wil, "Interface is down\n");
		goto out;
	}
	if (test_bit(wil_status_resetting, wil->status)) {
		wil_dbg_pm(wil, "Delay suspend when resetting\n");
		rc = -EBUSY;
		goto out;
	}
	if (wil->recovery_state != fw_recovery_idle) {
		wil_dbg_pm(wil, "Delay suspend during recovery\n");
		rc = -EBUSY;
		goto out;
	}

	/* interface is running */
	mutex_lock(&wil->vif_mutex);
	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		struct wil6210_vif *vif = wil->vifs[i];

		if (!vif)
			continue;
		if (!wil_can_suspend_vif(wil, vif, is_runtime)) {
			rc = -EBUSY;
			mutex_unlock(&wil->vif_mutex);
			goto out;
		}
	}
	mutex_unlock(&wil->vif_mutex);

out:
	wil_dbg_pm(wil, "can_suspend: %s => %s (%d)\n",
		   is_runtime ? "runtime" : "system", rc ? "No" : "Yes", rc);

	if (rc)
		wil->suspend_stats.rejected_by_host++;

	return rc;
}