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
struct ufs_pa_layer_attr {int /*<<< orphan*/  member_0; } ;
struct ufs_hba {int dummy; } ;
typedef  int /*<<< orphan*/  final_params ;

/* Variables and functions */
 int /*<<< orphan*/  PRE_CHANGE ; 
 int /*<<< orphan*/  memcpy (struct ufs_pa_layer_attr*,struct ufs_pa_layer_attr*,int) ; 
 int ufshcd_change_power_mode (struct ufs_hba*,struct ufs_pa_layer_attr*) ; 
 int /*<<< orphan*/  ufshcd_print_pwr_info (struct ufs_hba*) ; 
 int ufshcd_vops_pwr_change_notify (struct ufs_hba*,int /*<<< orphan*/ ,struct ufs_pa_layer_attr*,struct ufs_pa_layer_attr*) ; 

int ufshcd_config_pwr_mode(struct ufs_hba *hba,
		struct ufs_pa_layer_attr *desired_pwr_mode)
{
	struct ufs_pa_layer_attr final_params = { 0 };
	int ret;

	ret = ufshcd_vops_pwr_change_notify(hba, PRE_CHANGE,
					desired_pwr_mode, &final_params);

	if (ret)
		memcpy(&final_params, desired_pwr_mode, sizeof(final_params));

	ret = ufshcd_change_power_mode(hba, &final_params);
	if (!ret)
		ufshcd_print_pwr_info(hba);

	return ret;
}