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
struct ath10k {int /*<<< orphan*/  monitor_vdev_id; int /*<<< orphan*/  vdev_delete_done; int /*<<< orphan*/  vdev_setup_done; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ath10k_vdev_setup_sync (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_vdev_down (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_vdev_stop (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_monitor_vdev_stop(struct ath10k *ar)
{
	int ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_wmi_vdev_down(ar, ar->monitor_vdev_id);
	if (ret)
		ath10k_warn(ar, "failed to put down monitor vdev %i: %d\n",
			    ar->monitor_vdev_id, ret);

	reinit_completion(&ar->vdev_setup_done);
	reinit_completion(&ar->vdev_delete_done);

	ret = ath10k_wmi_vdev_stop(ar, ar->monitor_vdev_id);
	if (ret)
		ath10k_warn(ar, "failed to to request monitor vdev %i stop: %d\n",
			    ar->monitor_vdev_id, ret);

	ret = ath10k_vdev_setup_sync(ar);
	if (ret)
		ath10k_warn(ar, "failed to synchronize monitor vdev %i stop: %d\n",
			    ar->monitor_vdev_id, ret);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor vdev %i stopped\n",
		   ar->monitor_vdev_id);
	return ret;
}