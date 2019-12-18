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
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct ath10k {scalar_t__ num_started_vdevs; int /*<<< orphan*/  vdev_delete_done; int /*<<< orphan*/  vdev_setup_done; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath10k_recalc_radar_detection (struct ath10k*) ; 
 int ath10k_vdev_setup_sync (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_vdev_stop (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_vdev_stop(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_done);
	reinit_completion(&ar->vdev_delete_done);

	ret = ath10k_wmi_vdev_stop(ar, arvif->vdev_id);
	if (ret) {
		ath10k_warn(ar, "failed to stop WMI vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	ret = ath10k_vdev_setup_sync(ar);
	if (ret) {
		ath10k_warn(ar, "failed to synchronize setup for vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	WARN_ON(ar->num_started_vdevs == 0);

	if (ar->num_started_vdevs != 0) {
		ar->num_started_vdevs--;
		ath10k_recalc_radar_detection(ar);
	}

	return ret;
}