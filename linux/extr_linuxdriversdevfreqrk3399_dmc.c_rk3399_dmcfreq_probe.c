#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  downdifferential; int /*<<< orphan*/  upthreshold; } ;
struct TYPE_6__ {int /*<<< orphan*/  ddr3_speed_bin; } ;
struct rk3399_dmcfreq {struct device* dev; struct dev_pm_opp* devfreq; TYPE_4__ ondemand_data; int /*<<< orphan*/  rate; int /*<<< orphan*/  volt; struct dev_pm_opp* dmc_clk; TYPE_2__ timing; struct dev_pm_opp* edev; struct dev_pm_opp* vdd_center; int /*<<< orphan*/  lock; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct dram_timing {int dummy; } ;
struct device_node {int dummy; } ;
struct dev_pm_opp {int dummy; } ;
struct arm_smccc_res {scalar_t__ a0; } ;
struct TYPE_5__ {int /*<<< orphan*/  initial_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_SIMPLE_ONDEMAND ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  ROCKCHIP_SIP_CONFIG_DRAM_INIT ; 
 int /*<<< orphan*/  ROCKCHIP_SIP_CONFIG_DRAM_SET_PARAM ; 
 int /*<<< orphan*/  ROCKCHIP_SIP_DRAM_FREQ ; 
 int /*<<< orphan*/  arm_smccc_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 
 int /*<<< orphan*/  clk_get_rate (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_pm_opp_get_freq (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 scalar_t__ dev_pm_opp_of_add_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (struct device*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 int devfreq_event_enable_edev (struct dev_pm_opp*) ; 
 struct dev_pm_opp* devfreq_event_get_edev_by_phandle (struct device*,int /*<<< orphan*/ ) ; 
 struct dev_pm_opp* devfreq_recommended_opp (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dev_pm_opp* devm_clk_get (struct device*,char*) ; 
 struct dev_pm_opp* devm_devfreq_add_device (struct device*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  devm_devfreq_register_opp_notifier (struct device*,struct dev_pm_opp*) ; 
 struct rk3399_dmcfreq* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct dev_pm_opp* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_get_ddr_timings (TYPE_2__*,struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rk3399_dmcfreq*) ; 
 TYPE_1__ rk3399_devfreq_dmc_profile ; 

__attribute__((used)) static int rk3399_dmcfreq_probe(struct platform_device *pdev)
{
	struct arm_smccc_res res;
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct rk3399_dmcfreq *data;
	int ret, index, size;
	uint32_t *timing;
	struct dev_pm_opp *opp;

	data = devm_kzalloc(dev, sizeof(struct rk3399_dmcfreq), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	mutex_init(&data->lock);

	data->vdd_center = devm_regulator_get(dev, "center");
	if (IS_ERR(data->vdd_center)) {
		if (PTR_ERR(data->vdd_center) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_err(dev, "Cannot get the regulator \"center\"\n");
		return PTR_ERR(data->vdd_center);
	}

	data->dmc_clk = devm_clk_get(dev, "dmc_clk");
	if (IS_ERR(data->dmc_clk)) {
		if (PTR_ERR(data->dmc_clk) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_err(dev, "Cannot get the clk dmc_clk\n");
		return PTR_ERR(data->dmc_clk);
	};

	data->edev = devfreq_event_get_edev_by_phandle(dev, 0);
	if (IS_ERR(data->edev))
		return -EPROBE_DEFER;

	ret = devfreq_event_enable_edev(data->edev);
	if (ret < 0) {
		dev_err(dev, "failed to enable devfreq-event devices\n");
		return ret;
	}

	/*
	 * Get dram timing and pass it to arm trust firmware,
	 * the dram drvier in arm trust firmware will get these
	 * timing and to do dram initial.
	 */
	if (!of_get_ddr_timings(&data->timing, np)) {
		timing = &data->timing.ddr3_speed_bin;
		size = sizeof(struct dram_timing) / 4;
		for (index = 0; index < size; index++) {
			arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, *timing++, index,
				      ROCKCHIP_SIP_CONFIG_DRAM_SET_PARAM,
				      0, 0, 0, 0, &res);
			if (res.a0) {
				dev_err(dev, "Failed to set dram param: %ld\n",
					res.a0);
				return -EINVAL;
			}
		}
	}

	arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, 0, 0,
		      ROCKCHIP_SIP_CONFIG_DRAM_INIT,
		      0, 0, 0, 0, &res);

	/*
	 * We add a devfreq driver to our parent since it has a device tree node
	 * with operating points.
	 */
	if (dev_pm_opp_of_add_table(dev)) {
		dev_err(dev, "Invalid operating-points in device tree.\n");
		return -EINVAL;
	}

	of_property_read_u32(np, "upthreshold",
			     &data->ondemand_data.upthreshold);
	of_property_read_u32(np, "downdifferential",
			     &data->ondemand_data.downdifferential);

	data->rate = clk_get_rate(data->dmc_clk);

	opp = devfreq_recommended_opp(dev, &data->rate, 0);
	if (IS_ERR(opp)) {
		ret = PTR_ERR(opp);
		goto err_free_opp;
	}

	data->rate = dev_pm_opp_get_freq(opp);
	data->volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	rk3399_devfreq_dmc_profile.initial_freq = data->rate;

	data->devfreq = devm_devfreq_add_device(dev,
					   &rk3399_devfreq_dmc_profile,
					   DEVFREQ_GOV_SIMPLE_ONDEMAND,
					   &data->ondemand_data);
	if (IS_ERR(data->devfreq)) {
		ret = PTR_ERR(data->devfreq);
		goto err_free_opp;
	}

	devm_devfreq_register_opp_notifier(dev, data->devfreq);

	data->dev = dev;
	platform_set_drvdata(pdev, data);

	return 0;

err_free_opp:
	dev_pm_opp_of_remove_table(&pdev->dev);
	return ret;
}