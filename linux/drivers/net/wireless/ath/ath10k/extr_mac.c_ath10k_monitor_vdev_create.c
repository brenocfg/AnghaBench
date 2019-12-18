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
struct ath10k {long long free_vdev_map; int monitor_vdev_id; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WMI_VDEV_TYPE_MONITOR ; 
 int __ffs64 (long long) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,long long) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_vdev_create (struct ath10k*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_monitor_vdev_create(struct ath10k *ar)
{
	int bit, ret = 0;

	lockdep_assert_held(&ar->conf_mutex);

	if (ar->free_vdev_map == 0) {
		ath10k_warn(ar, "failed to find free vdev id for monitor vdev\n");
		return -ENOMEM;
	}

	bit = __ffs64(ar->free_vdev_map);

	ar->monitor_vdev_id = bit;

	ret = ath10k_wmi_vdev_create(ar, ar->monitor_vdev_id,
				     WMI_VDEV_TYPE_MONITOR,
				     0, ar->mac_addr);
	if (ret) {
		ath10k_warn(ar, "failed to request monitor vdev %i creation: %d\n",
			    ar->monitor_vdev_id, ret);
		return ret;
	}

	ar->free_vdev_map &= ~(1LL << ar->monitor_vdev_id);
	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac monitor vdev %d created\n",
		   ar->monitor_vdev_id);

	return 0;
}