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
struct dram_timing {int /*<<< orphan*/  phy_lpddr4_odt; int /*<<< orphan*/  phy_lpddr4_dq_drv; int /*<<< orphan*/  phy_lpddr4_ck_cs_drv; int /*<<< orphan*/  phy_lpddr4_ca_drv; int /*<<< orphan*/  lpddr4_ca_odt; int /*<<< orphan*/  lpddr4_dq_odt; int /*<<< orphan*/  lpddr4_drv; int /*<<< orphan*/  lpddr4_odt_dis_freq; int /*<<< orphan*/  phy_lpddr3_odt; int /*<<< orphan*/  phy_lpddr3_dq_drv; int /*<<< orphan*/  phy_lpddr3_ca_drv; int /*<<< orphan*/  lpddr3_odt; int /*<<< orphan*/  lpddr3_drv; int /*<<< orphan*/  lpddr3_odt_dis_freq; int /*<<< orphan*/  phy_ddr3_odt; int /*<<< orphan*/  phy_ddr3_dq_drv; int /*<<< orphan*/  phy_ddr3_ca_drv; int /*<<< orphan*/  ddr3_odt; int /*<<< orphan*/  ddr3_drv; int /*<<< orphan*/  ddr3_odt_dis_freq; int /*<<< orphan*/  phy_dll_dis_freq; int /*<<< orphan*/  dram_dll_dis_freq; int /*<<< orphan*/  auto_pd_dis_freq; int /*<<< orphan*/  standby_idle; int /*<<< orphan*/  srpd_lite_idle; int /*<<< orphan*/  sr_mc_gate_idle; int /*<<< orphan*/  sr_idle; int /*<<< orphan*/  pd_idle; int /*<<< orphan*/  ddr3_speed_bin; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int of_get_ddr_timings(struct dram_timing *timing,
			      struct device_node *np)
{
	int ret = 0;

	ret = of_property_read_u32(np, "rockchip,ddr3_speed_bin",
				   &timing->ddr3_speed_bin);
	ret |= of_property_read_u32(np, "rockchip,pd_idle",
				    &timing->pd_idle);
	ret |= of_property_read_u32(np, "rockchip,sr_idle",
				    &timing->sr_idle);
	ret |= of_property_read_u32(np, "rockchip,sr_mc_gate_idle",
				    &timing->sr_mc_gate_idle);
	ret |= of_property_read_u32(np, "rockchip,srpd_lite_idle",
				    &timing->srpd_lite_idle);
	ret |= of_property_read_u32(np, "rockchip,standby_idle",
				    &timing->standby_idle);
	ret |= of_property_read_u32(np, "rockchip,auto_pd_dis_freq",
				    &timing->auto_pd_dis_freq);
	ret |= of_property_read_u32(np, "rockchip,dram_dll_dis_freq",
				    &timing->dram_dll_dis_freq);
	ret |= of_property_read_u32(np, "rockchip,phy_dll_dis_freq",
				    &timing->phy_dll_dis_freq);
	ret |= of_property_read_u32(np, "rockchip,ddr3_odt_dis_freq",
				    &timing->ddr3_odt_dis_freq);
	ret |= of_property_read_u32(np, "rockchip,ddr3_drv",
				    &timing->ddr3_drv);
	ret |= of_property_read_u32(np, "rockchip,ddr3_odt",
				    &timing->ddr3_odt);
	ret |= of_property_read_u32(np, "rockchip,phy_ddr3_ca_drv",
				    &timing->phy_ddr3_ca_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_ddr3_dq_drv",
				    &timing->phy_ddr3_dq_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_ddr3_odt",
				    &timing->phy_ddr3_odt);
	ret |= of_property_read_u32(np, "rockchip,lpddr3_odt_dis_freq",
				    &timing->lpddr3_odt_dis_freq);
	ret |= of_property_read_u32(np, "rockchip,lpddr3_drv",
				    &timing->lpddr3_drv);
	ret |= of_property_read_u32(np, "rockchip,lpddr3_odt",
				    &timing->lpddr3_odt);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr3_ca_drv",
				    &timing->phy_lpddr3_ca_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr3_dq_drv",
				    &timing->phy_lpddr3_dq_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr3_odt",
				    &timing->phy_lpddr3_odt);
	ret |= of_property_read_u32(np, "rockchip,lpddr4_odt_dis_freq",
				    &timing->lpddr4_odt_dis_freq);
	ret |= of_property_read_u32(np, "rockchip,lpddr4_drv",
				    &timing->lpddr4_drv);
	ret |= of_property_read_u32(np, "rockchip,lpddr4_dq_odt",
				    &timing->lpddr4_dq_odt);
	ret |= of_property_read_u32(np, "rockchip,lpddr4_ca_odt",
				    &timing->lpddr4_ca_odt);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr4_ca_drv",
				    &timing->phy_lpddr4_ca_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr4_ck_cs_drv",
				    &timing->phy_lpddr4_ck_cs_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr4_dq_drv",
				    &timing->phy_lpddr4_dq_drv);
	ret |= of_property_read_u32(np, "rockchip,phy_lpddr4_odt",
				    &timing->phy_lpddr4_odt);

	return ret;
}