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
struct ath10k_vreg_info {int /*<<< orphan*/  reg; } ;
struct ath10k_snoc {struct ath10k_vreg_info* vreg; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ath10k_snoc_vreg_off (struct ath10k*,struct ath10k_vreg_info*) ; 
 int __ath10k_snoc_vreg_on (struct ath10k*,struct ath10k_vreg_info*) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  vreg_cfg ; 

__attribute__((used)) static int ath10k_snoc_vreg_on(struct ath10k *ar)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);
	struct ath10k_vreg_info *vreg_info;
	int ret = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(vreg_cfg); i++) {
		vreg_info = &ar_snoc->vreg[i];

		if (!vreg_info->reg)
			continue;

		ret = __ath10k_snoc_vreg_on(ar, vreg_info);
		if (ret)
			goto err_reg_config;
	}

	return 0;

err_reg_config:
	for (i = i - 1; i >= 0; i--) {
		vreg_info = &ar_snoc->vreg[i];

		if (!vreg_info->reg)
			continue;

		__ath10k_snoc_vreg_off(ar, vreg_info);
	}

	return ret;
}