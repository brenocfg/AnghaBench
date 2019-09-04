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
struct pp_atomfwctrl_smc_dpm_parameters {int /*<<< orphan*/  Vr2_I2C_address; int /*<<< orphan*/  acggfxclkspreadfreq; int /*<<< orphan*/  acggfxclkspreadpercent; int /*<<< orphan*/  acggfxclkspreadenabled; int /*<<< orphan*/  socclkspreadfreq; int /*<<< orphan*/  socclkspreadpercent; int /*<<< orphan*/  socclkspreadenabled; int /*<<< orphan*/  uclkspreadfreq; int /*<<< orphan*/  uclkspreadpercent; int /*<<< orphan*/  uclkspreadenabled; int /*<<< orphan*/  pllgfxclkspreadfreq; int /*<<< orphan*/  pllgfxclkspreadpercent; int /*<<< orphan*/  pllgfxclkspreadenabled; int /*<<< orphan*/  ledpin2; int /*<<< orphan*/  ledpin1; int /*<<< orphan*/  ledpin0; int /*<<< orphan*/  padding2; int /*<<< orphan*/  padding1; int /*<<< orphan*/  vr1hotpolarity; int /*<<< orphan*/  vr1hotgpio; int /*<<< orphan*/  vr0hotpolarity; int /*<<< orphan*/  vr0hotgpio; int /*<<< orphan*/  acdcpolarity; int /*<<< orphan*/  acdcgpio; int /*<<< orphan*/  padding_telemetrymem1; int /*<<< orphan*/  mem1offset; int /*<<< orphan*/  mem1maxcurrent; int /*<<< orphan*/  padding_telemetrymem0; int /*<<< orphan*/  mem0offset; int /*<<< orphan*/  mem0maxcurrent; int /*<<< orphan*/  padding_telemetrysoc; int /*<<< orphan*/  socoffset; int /*<<< orphan*/  socmaxcurrent; int /*<<< orphan*/  padding_telemetrygfx; int /*<<< orphan*/  gfxoffset; int /*<<< orphan*/  gfxmaxcurrent; int /*<<< orphan*/  soculvphasesheddingmask; int /*<<< orphan*/  gfxulvphasesheddingmask; int /*<<< orphan*/  vddmem1vrmapping; int /*<<< orphan*/  vddmem0vrmapping; int /*<<< orphan*/  vddsocvrmapping; int /*<<< orphan*/  vddgfxvrmapping; int /*<<< orphan*/  maxvoltagestepsoc; int /*<<< orphan*/  maxvoltagestepgfx; int /*<<< orphan*/  liquidsensorpresent; int /*<<< orphan*/  vrsensorpresent; int /*<<< orphan*/  plx_i2c_linesda; int /*<<< orphan*/  plx_i2c_linescl; int /*<<< orphan*/  vr_i2c_linesda; int /*<<< orphan*/  vr_i2c_linescl; int /*<<< orphan*/  liquid_i2c_linesda; int /*<<< orphan*/  liquid_i2c_linescl; int /*<<< orphan*/  plx_i2c_address; int /*<<< orphan*/  vr_i2c_address; int /*<<< orphan*/  liquid2_i2c_address; int /*<<< orphan*/  liquid1_i2c_address; } ;
struct atom_smc_dpm_info_v4_1 {int /*<<< orphan*/  Vr2_I2C_address; int /*<<< orphan*/  acggfxclkspreadfreq; int /*<<< orphan*/  acggfxclkspreadpercent; int /*<<< orphan*/  acggfxclkspreadenabled; int /*<<< orphan*/  socclkspreadfreq; int /*<<< orphan*/  socclkspreadpercent; int /*<<< orphan*/  socclkspreadenabled; int /*<<< orphan*/  uclkspreadfreq; int /*<<< orphan*/  uclkspreadpercent; int /*<<< orphan*/  uclkspreadenabled; int /*<<< orphan*/  pllgfxclkspreadfreq; int /*<<< orphan*/  pllgfxclkspreadpercent; int /*<<< orphan*/  pllgfxclkspreadenabled; int /*<<< orphan*/  ledpin2; int /*<<< orphan*/  ledpin1; int /*<<< orphan*/  ledpin0; int /*<<< orphan*/  padding2; int /*<<< orphan*/  padding1; int /*<<< orphan*/  vr1hotpolarity; int /*<<< orphan*/  vr1hotgpio; int /*<<< orphan*/  vr0hotpolarity; int /*<<< orphan*/  vr0hotgpio; int /*<<< orphan*/  acdcpolarity; int /*<<< orphan*/  acdcgpio; int /*<<< orphan*/  padding_telemetrymem1; int /*<<< orphan*/  mem1offset; int /*<<< orphan*/  mem1maxcurrent; int /*<<< orphan*/  padding_telemetrymem0; int /*<<< orphan*/  mem0offset; int /*<<< orphan*/  mem0maxcurrent; int /*<<< orphan*/  padding_telemetrysoc; int /*<<< orphan*/  socoffset; int /*<<< orphan*/  socmaxcurrent; int /*<<< orphan*/  padding_telemetrygfx; int /*<<< orphan*/  gfxoffset; int /*<<< orphan*/  gfxmaxcurrent; int /*<<< orphan*/  soculvphasesheddingmask; int /*<<< orphan*/  gfxulvphasesheddingmask; int /*<<< orphan*/  vddmem1vrmapping; int /*<<< orphan*/  vddmem0vrmapping; int /*<<< orphan*/  vddsocvrmapping; int /*<<< orphan*/  vddgfxvrmapping; int /*<<< orphan*/  maxvoltagestepsoc; int /*<<< orphan*/  maxvoltagestepgfx; int /*<<< orphan*/  liquidsensorpresent; int /*<<< orphan*/  vrsensorpresent; int /*<<< orphan*/  plx_i2c_linesda; int /*<<< orphan*/  plx_i2c_linescl; int /*<<< orphan*/  vr_i2c_linesda; int /*<<< orphan*/  vr_i2c_linescl; int /*<<< orphan*/  liquid_i2c_linesda; int /*<<< orphan*/  liquid_i2c_linescl; int /*<<< orphan*/  plx_i2c_address; int /*<<< orphan*/  vr_i2c_address; int /*<<< orphan*/  liquid2_i2c_address; int /*<<< orphan*/  liquid1_i2c_address; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GetIndexIntoMasterDataTable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  smc_dpm_info ; 
 scalar_t__ smu_atom_get_data_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pp_atomfwctrl_get_smc_dpm_information(struct pp_hwmgr *hwmgr,
		struct pp_atomfwctrl_smc_dpm_parameters *param)
{
	struct atom_smc_dpm_info_v4_1 *info;
	uint16_t ix;

	ix = GetIndexIntoMasterDataTable(smc_dpm_info);
	info = (struct atom_smc_dpm_info_v4_1 *)
		smu_atom_get_data_table(hwmgr->adev,
				ix, NULL, NULL, NULL);
	if (!info) {
		pr_info("Error retrieving BIOS Table Address!");
		return -EINVAL;
	}

	param->liquid1_i2c_address = info->liquid1_i2c_address;
	param->liquid2_i2c_address = info->liquid2_i2c_address;
	param->vr_i2c_address = info->vr_i2c_address;
	param->plx_i2c_address = info->plx_i2c_address;

	param->liquid_i2c_linescl = info->liquid_i2c_linescl;
	param->liquid_i2c_linesda = info->liquid_i2c_linesda;
	param->vr_i2c_linescl = info->vr_i2c_linescl;
	param->vr_i2c_linesda = info->vr_i2c_linesda;

	param->plx_i2c_linescl = info->plx_i2c_linescl;
	param->plx_i2c_linesda = info->plx_i2c_linesda;
	param->vrsensorpresent = info->vrsensorpresent;
	param->liquidsensorpresent = info->liquidsensorpresent;

	param->maxvoltagestepgfx = info->maxvoltagestepgfx;
	param->maxvoltagestepsoc = info->maxvoltagestepsoc;

	param->vddgfxvrmapping = info->vddgfxvrmapping;
	param->vddsocvrmapping = info->vddsocvrmapping;
	param->vddmem0vrmapping = info->vddmem0vrmapping;
	param->vddmem1vrmapping = info->vddmem1vrmapping;

	param->gfxulvphasesheddingmask = info->gfxulvphasesheddingmask;
	param->soculvphasesheddingmask = info->soculvphasesheddingmask;

	param->gfxmaxcurrent = info->gfxmaxcurrent;
	param->gfxoffset = info->gfxoffset;
	param->padding_telemetrygfx = info->padding_telemetrygfx;

	param->socmaxcurrent = info->socmaxcurrent;
	param->socoffset = info->socoffset;
	param->padding_telemetrysoc = info->padding_telemetrysoc;

	param->mem0maxcurrent = info->mem0maxcurrent;
	param->mem0offset = info->mem0offset;
	param->padding_telemetrymem0 = info->padding_telemetrymem0;

	param->mem1maxcurrent = info->mem1maxcurrent;
	param->mem1offset = info->mem1offset;
	param->padding_telemetrymem1 = info->padding_telemetrymem1;

	param->acdcgpio = info->acdcgpio;
	param->acdcpolarity = info->acdcpolarity;
	param->vr0hotgpio = info->vr0hotgpio;
	param->vr0hotpolarity = info->vr0hotpolarity;

	param->vr1hotgpio = info->vr1hotgpio;
	param->vr1hotpolarity = info->vr1hotpolarity;
	param->padding1 = info->padding1;
	param->padding2 = info->padding2;

	param->ledpin0 = info->ledpin0;
	param->ledpin1 = info->ledpin1;
	param->ledpin2 = info->ledpin2;

	param->pllgfxclkspreadenabled = info->pllgfxclkspreadenabled;
	param->pllgfxclkspreadpercent = info->pllgfxclkspreadpercent;
	param->pllgfxclkspreadfreq = info->pllgfxclkspreadfreq;

	param->uclkspreadenabled = info->uclkspreadenabled;
	param->uclkspreadpercent = info->uclkspreadpercent;
	param->uclkspreadfreq = info->uclkspreadfreq;

	param->socclkspreadenabled = info->socclkspreadenabled;
	param->socclkspreadpercent = info->socclkspreadpercent;
	param->socclkspreadfreq = info->socclkspreadfreq;

	param->acggfxclkspreadenabled = info->acggfxclkspreadenabled;
	param->acggfxclkspreadpercent = info->acggfxclkspreadpercent;
	param->acggfxclkspreadfreq = info->acggfxclkspreadfreq;

	param->Vr2_I2C_address = info->Vr2_I2C_address;

	return 0;
}