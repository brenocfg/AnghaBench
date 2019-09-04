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
typedef  int u16 ;

/* Variables and functions */
#define  MC_PMG_CMD_EMRS 141 
#define  MC_PMG_CMD_MRS 140 
#define  MC_PMG_CMD_MRS1 139 
#define  MC_PMG_CMD_MRS2 138 
#define  MC_SEQ_CAS_TIMING 137 
 int MC_SEQ_CAS_TIMING_LP ; 
#define  MC_SEQ_MISC_TIMING 136 
#define  MC_SEQ_MISC_TIMING2 135 
 int MC_SEQ_MISC_TIMING2_LP ; 
 int MC_SEQ_MISC_TIMING_LP ; 
 int MC_SEQ_PMG_CMD_EMRS_LP ; 
 int MC_SEQ_PMG_CMD_MRS1_LP ; 
 int MC_SEQ_PMG_CMD_MRS2_LP ; 
 int MC_SEQ_PMG_CMD_MRS_LP ; 
#define  MC_SEQ_PMG_TIMING 134 
 int MC_SEQ_PMG_TIMING_LP ; 
#define  MC_SEQ_RAS_TIMING 133 
 int MC_SEQ_RAS_TIMING_LP ; 
#define  MC_SEQ_RD_CTL_D0 132 
 int MC_SEQ_RD_CTL_D0_LP ; 
#define  MC_SEQ_RD_CTL_D1 131 
 int MC_SEQ_RD_CTL_D1_LP ; 
#define  MC_SEQ_WR_CTL_2 130 
 int MC_SEQ_WR_CTL_2_LP ; 
#define  MC_SEQ_WR_CTL_D0 129 
 int MC_SEQ_WR_CTL_D0_LP ; 
#define  MC_SEQ_WR_CTL_D1 128 
 int MC_SEQ_WR_CTL_D1_LP ; 

__attribute__((used)) static bool si_check_s0_mc_reg_index(u16 in_reg, u16 *out_reg)
{
	bool result = true;
	switch (in_reg) {
	case  MC_SEQ_RAS_TIMING:
		*out_reg = MC_SEQ_RAS_TIMING_LP;
		break;
	case MC_SEQ_CAS_TIMING:
		*out_reg = MC_SEQ_CAS_TIMING_LP;
		break;
	case MC_SEQ_MISC_TIMING:
		*out_reg = MC_SEQ_MISC_TIMING_LP;
		break;
	case MC_SEQ_MISC_TIMING2:
		*out_reg = MC_SEQ_MISC_TIMING2_LP;
		break;
	case MC_SEQ_RD_CTL_D0:
		*out_reg = MC_SEQ_RD_CTL_D0_LP;
		break;
	case MC_SEQ_RD_CTL_D1:
		*out_reg = MC_SEQ_RD_CTL_D1_LP;
		break;
	case MC_SEQ_WR_CTL_D0:
		*out_reg = MC_SEQ_WR_CTL_D0_LP;
		break;
	case MC_SEQ_WR_CTL_D1:
		*out_reg = MC_SEQ_WR_CTL_D1_LP;
		break;
	case MC_PMG_CMD_EMRS:
		*out_reg = MC_SEQ_PMG_CMD_EMRS_LP;
		break;
	case MC_PMG_CMD_MRS:
		*out_reg = MC_SEQ_PMG_CMD_MRS_LP;
		break;
	case MC_PMG_CMD_MRS1:
		*out_reg = MC_SEQ_PMG_CMD_MRS1_LP;
		break;
	case MC_SEQ_PMG_TIMING:
		*out_reg = MC_SEQ_PMG_TIMING_LP;
		break;
	case MC_PMG_CMD_MRS2:
		*out_reg = MC_SEQ_PMG_CMD_MRS2_LP;
		break;
	case MC_SEQ_WR_CTL_2:
		*out_reg = MC_SEQ_WR_CTL_2_LP;
		break;
	default:
		result = false;
		break;
	}

	return result;
}