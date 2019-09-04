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
typedef  int /*<<< orphan*/  uint16_t ;
struct pp_hwmgr {int /*<<< orphan*/  adev; } ;
struct pp_atomfwctrl_gpio_parameters {int /*<<< orphan*/  ucFwCtfPolarity; int /*<<< orphan*/  ucFwCtfGpio; int /*<<< orphan*/  ucVR1HotPolarity; int /*<<< orphan*/  ucVR1HotGpio; int /*<<< orphan*/  ucVR0HotPolarity; int /*<<< orphan*/  ucVR0HotGpio; int /*<<< orphan*/  ucAcDcPolarity; int /*<<< orphan*/  ucAcDcGpio; } ;
struct atom_smu_info_v3_1 {int /*<<< orphan*/  fw_ctf_polarity; int /*<<< orphan*/  fw_ctf_gpio_bit; int /*<<< orphan*/  vr1hot_polarity; int /*<<< orphan*/  vr1hot_gpio_bit; int /*<<< orphan*/  vr0hot_polarity; int /*<<< orphan*/  vr0hot_gpio_bit; int /*<<< orphan*/  ac_dc_polarity; int /*<<< orphan*/  ac_dc_gpio_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetIndexIntoMasterDataTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smu_info ; 

int pp_atomfwctrl_get_gpio_information(struct pp_hwmgr *hwmgr,
		struct pp_atomfwctrl_gpio_parameters *param)
{
	struct atom_smu_info_v3_1 *info;
	uint16_t idx;

	idx = GetIndexIntoMasterDataTable(smu_info);
	info = (struct atom_smu_info_v3_1 *)
		smu_atom_get_data_table(hwmgr->adev,
				idx, NULL, NULL, NULL);

	if (!info) {
		pr_info("Error retrieving BIOS smu_info Table Address!");
		return -1;
	}

	param->ucAcDcGpio       = info->ac_dc_gpio_bit;
	param->ucAcDcPolarity   = info->ac_dc_polarity;
	param->ucVR0HotGpio     = info->vr0hot_gpio_bit;
	param->ucVR0HotPolarity = info->vr0hot_polarity;
	param->ucVR1HotGpio     = info->vr1hot_gpio_bit;
	param->ucVR1HotPolarity = info->vr1hot_polarity;
	param->ucFwCtfGpio      = info->fw_ctf_gpio_bit;
	param->ucFwCtfPolarity  = info->fw_ctf_polarity;

	return 0;
}