#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* vMPLL_SS2; void* vMPLL_SS1; void* vMPLL_FUNC_CNTL_2; void* vMPLL_FUNC_CNTL_1; void* vMPLL_FUNC_CNTL; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL; void* vMCLK_PWRMGT_CNTL; void* vDLL_CNTL; void* vCG_SPLL_SPREAD_SPECTRUM_2; void* vCG_SPLL_SPREAD_SPECTRUM; void* vCG_SPLL_FUNC_CNTL_4; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; } ;
struct smu7_hwmgr {TYPE_1__ clock_registers; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 void* cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cgs_read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL_2 ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL_3 ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL_4 ; 
 int /*<<< orphan*/  ixCG_SPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  ixCG_SPLL_SPREAD_SPECTRUM_2 ; 
 int /*<<< orphan*/  mmDLL_CNTL ; 
 int /*<<< orphan*/  mmMCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  mmMPLL_AD_FUNC_CNTL ; 
 int /*<<< orphan*/  mmMPLL_DQ_FUNC_CNTL ; 
 int /*<<< orphan*/  mmMPLL_FUNC_CNTL ; 
 int /*<<< orphan*/  mmMPLL_FUNC_CNTL_1 ; 
 int /*<<< orphan*/  mmMPLL_FUNC_CNTL_2 ; 
 int /*<<< orphan*/  mmMPLL_SS1 ; 
 int /*<<< orphan*/  mmMPLL_SS2 ; 

__attribute__((used)) static int smu7_read_clock_registers(struct pp_hwmgr *hwmgr)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	data->clock_registers.vCG_SPLL_FUNC_CNTL         =
		cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL);
	data->clock_registers.vCG_SPLL_FUNC_CNTL_2       =
		cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL_2);
	data->clock_registers.vCG_SPLL_FUNC_CNTL_3       =
		cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL_3);
	data->clock_registers.vCG_SPLL_FUNC_CNTL_4       =
		cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_FUNC_CNTL_4);
	data->clock_registers.vCG_SPLL_SPREAD_SPECTRUM   =
		cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_SPREAD_SPECTRUM);
	data->clock_registers.vCG_SPLL_SPREAD_SPECTRUM_2 =
		cgs_read_ind_register(hwmgr->device, CGS_IND_REG__SMC, ixCG_SPLL_SPREAD_SPECTRUM_2);
	data->clock_registers.vDLL_CNTL                  =
		cgs_read_register(hwmgr->device, mmDLL_CNTL);
	data->clock_registers.vMCLK_PWRMGT_CNTL          =
		cgs_read_register(hwmgr->device, mmMCLK_PWRMGT_CNTL);
	data->clock_registers.vMPLL_AD_FUNC_CNTL         =
		cgs_read_register(hwmgr->device, mmMPLL_AD_FUNC_CNTL);
	data->clock_registers.vMPLL_DQ_FUNC_CNTL         =
		cgs_read_register(hwmgr->device, mmMPLL_DQ_FUNC_CNTL);
	data->clock_registers.vMPLL_FUNC_CNTL            =
		cgs_read_register(hwmgr->device, mmMPLL_FUNC_CNTL);
	data->clock_registers.vMPLL_FUNC_CNTL_1          =
		cgs_read_register(hwmgr->device, mmMPLL_FUNC_CNTL_1);
	data->clock_registers.vMPLL_FUNC_CNTL_2          =
		cgs_read_register(hwmgr->device, mmMPLL_FUNC_CNTL_2);
	data->clock_registers.vMPLL_SS1                  =
		cgs_read_register(hwmgr->device, mmMPLL_SS1);
	data->clock_registers.vMPLL_SS2                  =
		cgs_read_register(hwmgr->device, mmMPLL_SS2);
	return 0;

}