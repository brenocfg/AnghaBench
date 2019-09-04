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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ last; TYPE_1__* mc_reg_address; } ;
struct evergreen_power_info {TYPE_2__ mc_reg_table; } ;
struct TYPE_3__ {int s0; int s1; } ;

/* Variables and functions */
 int MC_PMG_CMD_EMRS ; 
 int MC_PMG_CMD_MRS ; 
 int MC_PMG_CMD_MRS1 ; 
 int MC_SEQ_CAS_TIMING ; 
 int MC_SEQ_CAS_TIMING_LP ; 
 int MC_SEQ_MISC1 ; 
 int MC_SEQ_MISC3 ; 
 int MC_SEQ_MISC_TIMING ; 
 int MC_SEQ_MISC_TIMING2 ; 
 int MC_SEQ_MISC_TIMING2_LP ; 
 int MC_SEQ_MISC_TIMING_LP ; 
 int MC_SEQ_PMG_CMD_EMRS_LP ; 
 int MC_SEQ_PMG_CMD_MRS1_LP ; 
 int MC_SEQ_PMG_CMD_MRS_LP ; 
 int MC_SEQ_RAS_TIMING ; 
 int MC_SEQ_RAS_TIMING_LP ; 
 int MC_SEQ_RD_CTL_D0 ; 
 int MC_SEQ_RD_CTL_D0_LP ; 
 int MC_SEQ_RD_CTL_D1 ; 
 int MC_SEQ_RD_CTL_D1_LP ; 
 int MC_SEQ_RESERVE_M ; 
 int MC_SEQ_WR_CTL_D0 ; 
 int MC_SEQ_WR_CTL_D0_LP ; 
 int MC_SEQ_WR_CTL_D1 ; 
 int MC_SEQ_WR_CTL_D1_LP ; 
 struct evergreen_power_info* evergreen_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void cypress_set_mc_reg_address_table(struct radeon_device *rdev)
{
	struct evergreen_power_info *eg_pi = evergreen_get_pi(rdev);
	u32 i = 0;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RAS_TIMING_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RAS_TIMING >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_CAS_TIMING_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_CAS_TIMING >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC_TIMING_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC_TIMING >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC_TIMING2_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC_TIMING2 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RD_CTL_D0_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RD_CTL_D0 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RD_CTL_D1_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RD_CTL_D1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_WR_CTL_D0_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_WR_CTL_D0 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_WR_CTL_D1_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_WR_CTL_D1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_PMG_CMD_EMRS_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_PMG_CMD_EMRS >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_PMG_CMD_MRS_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_PMG_CMD_MRS >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_PMG_CMD_MRS1_LP >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_PMG_CMD_MRS1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC1 >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC1 >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_RESERVE_M >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_RESERVE_M >> 2;
	i++;

	eg_pi->mc_reg_table.mc_reg_address[i].s0 = MC_SEQ_MISC3 >> 2;
	eg_pi->mc_reg_table.mc_reg_address[i].s1 = MC_SEQ_MISC3 >> 2;
	i++;

	eg_pi->mc_reg_table.last = (u8)i;
}