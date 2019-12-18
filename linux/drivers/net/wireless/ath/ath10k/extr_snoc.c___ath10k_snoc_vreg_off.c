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
struct ath10k_vreg_info {int /*<<< orphan*/  name; int /*<<< orphan*/  max_v; int /*<<< orphan*/  reg; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_set_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ath10k_snoc_vreg_off(struct ath10k *ar,
				  struct ath10k_vreg_info *vreg_info)
{
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc regulator %s being disabled\n",
		   vreg_info->name);

	ret = regulator_disable(vreg_info->reg);
	if (ret)
		ath10k_err(ar, "failed to disable regulator %s\n",
			   vreg_info->name);

	ret = regulator_set_load(vreg_info->reg, 0);
	if (ret < 0)
		ath10k_err(ar, "failed to set load %s\n", vreg_info->name);

	ret = regulator_set_voltage(vreg_info->reg, 0, vreg_info->max_v);
	if (ret)
		ath10k_err(ar, "failed to set voltage %s\n", vreg_info->name);

	return ret;
}