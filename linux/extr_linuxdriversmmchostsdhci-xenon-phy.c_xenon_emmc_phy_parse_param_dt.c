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
typedef  int u32 ;
struct xenon_emmc_phy_params {int slow_mode; int znr; int zpr; int nr_tun_times; int tun_step_divider; } ;
struct sdhci_host {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int XENON_TUNING_STEP_DIVIDER ; 
 int XENON_TUN_CONSECUTIVE_TIMES ; 
 int XENON_TUN_CONSECUTIVE_TIMES_MASK ; 
 int XENON_ZNR_DEF_VALUE ; 
 int XENON_ZNR_MASK ; 
 int XENON_ZPR_DEF_VALUE ; 
 int XENON_ZPR_MASK ; 
 int get_dt_pad_ctrl_data (struct sdhci_host*,struct device_node*,struct xenon_emmc_phy_params*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int xenon_emmc_phy_parse_param_dt(struct sdhci_host *host,
					 struct device_node *np,
					 struct xenon_emmc_phy_params *params)
{
	u32 value;

	params->slow_mode = false;
	if (of_property_read_bool(np, "marvell,xenon-phy-slow-mode"))
		params->slow_mode = true;

	params->znr = XENON_ZNR_DEF_VALUE;
	if (!of_property_read_u32(np, "marvell,xenon-phy-znr", &value))
		params->znr = value & XENON_ZNR_MASK;

	params->zpr = XENON_ZPR_DEF_VALUE;
	if (!of_property_read_u32(np, "marvell,xenon-phy-zpr", &value))
		params->zpr = value & XENON_ZPR_MASK;

	params->nr_tun_times = XENON_TUN_CONSECUTIVE_TIMES;
	if (!of_property_read_u32(np, "marvell,xenon-phy-nr-success-tun",
				  &value))
		params->nr_tun_times = value & XENON_TUN_CONSECUTIVE_TIMES_MASK;

	params->tun_step_divider = XENON_TUNING_STEP_DIVIDER;
	if (!of_property_read_u32(np, "marvell,xenon-phy-tun-step-divider",
				  &value))
		params->tun_step_divider = value & 0xFF;

	return get_dt_pad_ctrl_data(host, np, params);
}