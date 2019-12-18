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
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ath10k_vif {int /*<<< orphan*/  vdev_id; } ;
struct TYPE_4__ {TYPE_1__* vdev_param; } ;
struct ath10k {TYPE_2__ wmi; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_3__ {int /*<<< orphan*/  inc_tsf; int /*<<< orphan*/  dec_tsf; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_vdev_set_param (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_offset_tsf(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif, s64 tsf_offset)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	u32 offset, vdev_param;
	int ret;

	if (tsf_offset < 0) {
		vdev_param = ar->wmi.vdev_param->dec_tsf;
		offset = -tsf_offset;
	} else {
		vdev_param = ar->wmi.vdev_param->inc_tsf;
		offset = tsf_offset;
	}

	ret = ath10k_wmi_vdev_set_param(ar, arvif->vdev_id,
					vdev_param, offset);

	if (ret && ret != -EOPNOTSUPP)
		ath10k_warn(ar, "failed to set tsf offset %d cmd %d: %d\n",
			    offset, vdev_param, ret);
}