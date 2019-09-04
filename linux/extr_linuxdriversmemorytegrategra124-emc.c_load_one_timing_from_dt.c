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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_emc {int /*<<< orphan*/  dev; } ;
struct emc_timing {int /*<<< orphan*/  emc_zcal_interval; int /*<<< orphan*/  emc_zcal_cnt_long; int /*<<< orphan*/  emc_xm2dqspadctrl2; int /*<<< orphan*/  emc_sel_dpd_ctrl; int /*<<< orphan*/  emc_mrs_wait_cnt; int /*<<< orphan*/  emc_mode_reset; int /*<<< orphan*/  emc_mode_4; int /*<<< orphan*/  emc_mode_2; int /*<<< orphan*/  emc_mode_1; int /*<<< orphan*/  emc_ctt_term_ctrl; int /*<<< orphan*/  emc_cfg_2; int /*<<< orphan*/  emc_cfg; int /*<<< orphan*/  emc_bgbias_ctl0; int /*<<< orphan*/  emc_auto_cal_interval; int /*<<< orphan*/  emc_auto_cal_config3; int /*<<< orphan*/  emc_auto_cal_config2; int /*<<< orphan*/  emc_auto_cal_config; int /*<<< orphan*/  emc_burst_data; int /*<<< orphan*/  rate; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_one_timing_from_dt(struct tegra_emc *emc,
				   struct emc_timing *timing,
				   struct device_node *node)
{
	u32 value;
	int err;

	err = of_property_read_u32(node, "clock-frequency", &value);
	if (err) {
		dev_err(emc->dev, "timing %s: failed to read rate: %d\n",
			node->name, err);
		return err;
	}

	timing->rate = value;

	err = of_property_read_u32_array(node, "nvidia,emc-configuration",
					 timing->emc_burst_data,
					 ARRAY_SIZE(timing->emc_burst_data));
	if (err) {
		dev_err(emc->dev,
			"timing %s: failed to read emc burst data: %d\n",
			node->name, err);
		return err;
	}

#define EMC_READ_PROP(prop, dtprop) { \
	err = of_property_read_u32(node, dtprop, &timing->prop); \
	if (err) { \
		dev_err(emc->dev, "timing %s: failed to read " #prop ": %d\n", \
			node->name, err); \
		return err; \
	} \
}

	EMC_READ_PROP(emc_auto_cal_config, "nvidia,emc-auto-cal-config")
	EMC_READ_PROP(emc_auto_cal_config2, "nvidia,emc-auto-cal-config2")
	EMC_READ_PROP(emc_auto_cal_config3, "nvidia,emc-auto-cal-config3")
	EMC_READ_PROP(emc_auto_cal_interval, "nvidia,emc-auto-cal-interval")
	EMC_READ_PROP(emc_bgbias_ctl0, "nvidia,emc-bgbias-ctl0")
	EMC_READ_PROP(emc_cfg, "nvidia,emc-cfg")
	EMC_READ_PROP(emc_cfg_2, "nvidia,emc-cfg-2")
	EMC_READ_PROP(emc_ctt_term_ctrl, "nvidia,emc-ctt-term-ctrl")
	EMC_READ_PROP(emc_mode_1, "nvidia,emc-mode-1")
	EMC_READ_PROP(emc_mode_2, "nvidia,emc-mode-2")
	EMC_READ_PROP(emc_mode_4, "nvidia,emc-mode-4")
	EMC_READ_PROP(emc_mode_reset, "nvidia,emc-mode-reset")
	EMC_READ_PROP(emc_mrs_wait_cnt, "nvidia,emc-mrs-wait-cnt")
	EMC_READ_PROP(emc_sel_dpd_ctrl, "nvidia,emc-sel-dpd-ctrl")
	EMC_READ_PROP(emc_xm2dqspadctrl2, "nvidia,emc-xm2dqspadctrl2")
	EMC_READ_PROP(emc_zcal_cnt_long, "nvidia,emc-zcal-cnt-long")
	EMC_READ_PROP(emc_zcal_interval, "nvidia,emc-zcal-interval")

#undef EMC_READ_PROP

	return 0;
}