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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_vif {scalar_t__ num_legacy_stations; int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_3__ {TYPE_2__* vdev_param; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  conf_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  enable_rtscts; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_RTSCTS_ACROSS_SW_RETRIES ; 
 int /*<<< orphan*/  WMI_RTSCTS_ENABLED ; 
 int /*<<< orphan*/  WMI_RTSCTS_FOR_SECOND_RATESERIES ; 
 int /*<<< orphan*/  WMI_RTSCTS_PROFILE ; 
 int /*<<< orphan*/  WMI_RTSCTS_SET ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_recalc_rtscts_prot(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	u32 vdev_param, rts_cts = 0;

	lockdep_assert_held(&ar->conf_mutex);

	vdev_param = ar->wmi.vdev_param->enable_rtscts;

	rts_cts |= SM(WMI_RTSCTS_ENABLED, WMI_RTSCTS_SET);

	if (arvif->num_legacy_stations > 0)
		rts_cts |= SM(WMI_RTSCTS_ACROSS_SW_RETRIES,
			      WMI_RTSCTS_PROFILE);
	else
		rts_cts |= SM(WMI_RTSCTS_FOR_SECOND_RATESERIES,
			      WMI_RTSCTS_PROFILE);

	ath10k_dbg(ar, ATH10K_DBG_MAC, "mac vdev %d recalc rts/cts prot %d\n",
		   arvif->vdev_id, rts_cts);

	return ath10k_wmi_vdev_set_param(ar, arvif->vdev_id, vdev_param,
					 rts_cts);
}