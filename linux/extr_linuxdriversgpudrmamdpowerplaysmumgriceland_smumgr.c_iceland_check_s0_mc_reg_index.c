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
typedef  int uint16_t ;

/* Variables and functions */
#define  mmMC_PMG_CMD_EMRS 147 
#define  mmMC_PMG_CMD_MRS 146 
#define  mmMC_PMG_CMD_MRS1 145 
#define  mmMC_PMG_CMD_MRS2 144 
#define  mmMC_SEQ_CAS_TIMING 143 
 int mmMC_SEQ_CAS_TIMING_LP ; 
#define  mmMC_SEQ_DLL_STBY 142 
 int mmMC_SEQ_DLL_STBY_LP ; 
#define  mmMC_SEQ_G5PDX_CMD0 141 
 int mmMC_SEQ_G5PDX_CMD0_LP ; 
#define  mmMC_SEQ_G5PDX_CMD1 140 
 int mmMC_SEQ_G5PDX_CMD1_LP ; 
#define  mmMC_SEQ_G5PDX_CTRL 139 
 int mmMC_SEQ_G5PDX_CTRL_LP ; 
#define  mmMC_SEQ_MISC_TIMING 138 
#define  mmMC_SEQ_MISC_TIMING2 137 
 int mmMC_SEQ_MISC_TIMING2_LP ; 
 int mmMC_SEQ_MISC_TIMING_LP ; 
 int mmMC_SEQ_PMG_CMD_EMRS_LP ; 
 int mmMC_SEQ_PMG_CMD_MRS1_LP ; 
 int mmMC_SEQ_PMG_CMD_MRS2_LP ; 
 int mmMC_SEQ_PMG_CMD_MRS_LP ; 
#define  mmMC_SEQ_PMG_DVS_CMD 136 
 int mmMC_SEQ_PMG_DVS_CMD_LP ; 
#define  mmMC_SEQ_PMG_DVS_CTL 135 
 int mmMC_SEQ_PMG_DVS_CTL_LP ; 
#define  mmMC_SEQ_PMG_TIMING 134 
 int mmMC_SEQ_PMG_TIMING_LP ; 
#define  mmMC_SEQ_RAS_TIMING 133 
 int mmMC_SEQ_RAS_TIMING_LP ; 
#define  mmMC_SEQ_RD_CTL_D0 132 
 int mmMC_SEQ_RD_CTL_D0_LP ; 
#define  mmMC_SEQ_RD_CTL_D1 131 
 int mmMC_SEQ_RD_CTL_D1_LP ; 
#define  mmMC_SEQ_WR_CTL_2 130 
 int mmMC_SEQ_WR_CTL_2_LP ; 
#define  mmMC_SEQ_WR_CTL_D0 129 
 int mmMC_SEQ_WR_CTL_D0_LP ; 
#define  mmMC_SEQ_WR_CTL_D1 128 
 int mmMC_SEQ_WR_CTL_D1_LP ; 

__attribute__((used)) static bool iceland_check_s0_mc_reg_index(uint16_t in_reg, uint16_t *out_reg)
{
	bool result = true;

	switch (in_reg) {
	case  mmMC_SEQ_RAS_TIMING:
		*out_reg = mmMC_SEQ_RAS_TIMING_LP;
		break;

	case  mmMC_SEQ_DLL_STBY:
		*out_reg = mmMC_SEQ_DLL_STBY_LP;
		break;

	case  mmMC_SEQ_G5PDX_CMD0:
		*out_reg = mmMC_SEQ_G5PDX_CMD0_LP;
		break;

	case  mmMC_SEQ_G5PDX_CMD1:
		*out_reg = mmMC_SEQ_G5PDX_CMD1_LP;
		break;

	case  mmMC_SEQ_G5PDX_CTRL:
		*out_reg = mmMC_SEQ_G5PDX_CTRL_LP;
		break;

	case mmMC_SEQ_CAS_TIMING:
		*out_reg = mmMC_SEQ_CAS_TIMING_LP;
		break;

	case mmMC_SEQ_MISC_TIMING:
		*out_reg = mmMC_SEQ_MISC_TIMING_LP;
		break;

	case mmMC_SEQ_MISC_TIMING2:
		*out_reg = mmMC_SEQ_MISC_TIMING2_LP;
		break;

	case mmMC_SEQ_PMG_DVS_CMD:
		*out_reg = mmMC_SEQ_PMG_DVS_CMD_LP;
		break;

	case mmMC_SEQ_PMG_DVS_CTL:
		*out_reg = mmMC_SEQ_PMG_DVS_CTL_LP;
		break;

	case mmMC_SEQ_RD_CTL_D0:
		*out_reg = mmMC_SEQ_RD_CTL_D0_LP;
		break;

	case mmMC_SEQ_RD_CTL_D1:
		*out_reg = mmMC_SEQ_RD_CTL_D1_LP;
		break;

	case mmMC_SEQ_WR_CTL_D0:
		*out_reg = mmMC_SEQ_WR_CTL_D0_LP;
		break;

	case mmMC_SEQ_WR_CTL_D1:
		*out_reg = mmMC_SEQ_WR_CTL_D1_LP;
		break;

	case mmMC_PMG_CMD_EMRS:
		*out_reg = mmMC_SEQ_PMG_CMD_EMRS_LP;
		break;

	case mmMC_PMG_CMD_MRS:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS_LP;
		break;

	case mmMC_PMG_CMD_MRS1:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS1_LP;
		break;

	case mmMC_SEQ_PMG_TIMING:
		*out_reg = mmMC_SEQ_PMG_TIMING_LP;
		break;

	case mmMC_PMG_CMD_MRS2:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS2_LP;
		break;

	case mmMC_SEQ_WR_CTL_2:
		*out_reg = mmMC_SEQ_WR_CTL_2_LP;
		break;

	default:
		result = false;
		break;
	}

	return result;
}