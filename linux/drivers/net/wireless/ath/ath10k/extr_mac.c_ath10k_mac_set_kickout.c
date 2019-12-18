#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_6__ {TYPE_2__* vdev_param; TYPE_1__* pdev_param; } ;
struct ath10k {TYPE_3__ wmi; } ;
struct TYPE_5__ {int /*<<< orphan*/  ap_keepalive_max_unresponsive_time_secs; int /*<<< orphan*/  ap_keepalive_max_idle_inactive_time_secs; int /*<<< orphan*/  ap_keepalive_min_idle_inactive_time_secs; } ;
struct TYPE_4__ {int /*<<< orphan*/  sta_kickout_th; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_KEEPALIVE_MAX_IDLE ; 
 int /*<<< orphan*/  ATH10K_KEEPALIVE_MAX_UNRESPONSIVE ; 
 int /*<<< orphan*/  ATH10K_KEEPALIVE_MIN_IDLE ; 
 int /*<<< orphan*/  ATH10K_KICKOUT_THRESHOLD ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_pdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_set_kickout(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	u32 param;
	int ret;

	param = ar->wmi.pdev_param->sta_kickout_th;
	ret = ath10k_wmi_pdev_set_param(ar, param,
					ATH10K_KICKOUT_THRESHOLD);
	if (ret) {
		ath10k_warn(ar, "failed to set kickout threshold on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = ar->wmi.vdev_param->ap_keepalive_min_idle_inactive_time_secs;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, param,
					ATH10K_KEEPALIVE_MIN_IDLE);
	if (ret) {
		ath10k_warn(ar, "failed to set keepalive minimum idle time on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = ar->wmi.vdev_param->ap_keepalive_max_idle_inactive_time_secs;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, param,
					ATH10K_KEEPALIVE_MAX_IDLE);
	if (ret) {
		ath10k_warn(ar, "failed to set keepalive maximum idle time on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	param = ar->wmi.vdev_param->ap_keepalive_max_unresponsive_time_secs;
	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, param,
					ATH10K_KEEPALIVE_MAX_UNRESPONSIVE);
	if (ret) {
		ath10k_warn(ar, "failed to set keepalive maximum unresponsive time on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}