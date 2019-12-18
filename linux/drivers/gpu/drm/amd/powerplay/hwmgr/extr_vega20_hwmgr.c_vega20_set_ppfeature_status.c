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
typedef  unsigned long long uint64_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long long GNLD_FEATURES_MAX ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long) ; 
 int vega20_enable_smc_features (struct pp_hwmgr*,int,unsigned long long) ; 
 int vega20_get_enabled_smc_features (struct pp_hwmgr*,unsigned long long*) ; 

__attribute__((used)) static int vega20_set_ppfeature_status(struct pp_hwmgr *hwmgr, uint64_t new_ppfeature_masks)
{
	uint64_t features_enabled;
	uint64_t features_to_enable;
	uint64_t features_to_disable;
	int ret = 0;

	if (new_ppfeature_masks >= (1ULL << GNLD_FEATURES_MAX))
		return -EINVAL;

	ret = vega20_get_enabled_smc_features(hwmgr, &features_enabled);
	if (ret)
		return ret;

	features_to_disable =
		features_enabled & ~new_ppfeature_masks;
	features_to_enable =
		~features_enabled & new_ppfeature_masks;

	pr_debug("features_to_disable 0x%llx\n", features_to_disable);
	pr_debug("features_to_enable 0x%llx\n", features_to_enable);

	if (features_to_disable) {
		ret = vega20_enable_smc_features(hwmgr, false, features_to_disable);
		if (ret)
			return ret;
	}

	if (features_to_enable) {
		ret = vega20_enable_smc_features(hwmgr, true, features_to_enable);
		if (ret)
			return ret;
	}

	return 0;
}