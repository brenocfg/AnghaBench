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
struct tegra_dfll_soc_data {int /*<<< orphan*/  max_freq; int /*<<< orphan*/  cvb; int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int cpu_process_id; int cpu_speedo_id; int cpu_speedo_value; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpu_max_freq_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct tegra_dfll_soc_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpu_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tegra124_cpu_cvb_tables ; 
 int /*<<< orphan*/  tegra_cvb_add_opp_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_cvb_remove_opp_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tegra_dfll_register (struct platform_device*,struct tegra_dfll_soc_data*) ; 
 TYPE_1__ tegra_sku_info ; 

__attribute__((used)) static int tegra124_dfll_fcpu_probe(struct platform_device *pdev)
{
	int process_id, speedo_id, speedo_value, err;
	struct tegra_dfll_soc_data *soc;

	process_id = tegra_sku_info.cpu_process_id;
	speedo_id = tegra_sku_info.cpu_speedo_id;
	speedo_value = tegra_sku_info.cpu_speedo_value;

	if (speedo_id >= ARRAY_SIZE(cpu_max_freq_table)) {
		dev_err(&pdev->dev, "unknown max CPU freq for speedo_id=%d\n",
			speedo_id);
		return -ENODEV;
	}

	soc = devm_kzalloc(&pdev->dev, sizeof(*soc), GFP_KERNEL);
	if (!soc)
		return -ENOMEM;

	soc->dev = get_cpu_device(0);
	if (!soc->dev) {
		dev_err(&pdev->dev, "no CPU0 device\n");
		return -ENODEV;
	}

	soc->max_freq = cpu_max_freq_table[speedo_id];

	soc->cvb = tegra_cvb_add_opp_table(soc->dev, tegra124_cpu_cvb_tables,
					   ARRAY_SIZE(tegra124_cpu_cvb_tables),
					   process_id, speedo_id, speedo_value,
					   soc->max_freq);
	if (IS_ERR(soc->cvb)) {
		dev_err(&pdev->dev, "couldn't add OPP table: %ld\n",
			PTR_ERR(soc->cvb));
		return PTR_ERR(soc->cvb);
	}

	err = tegra_dfll_register(pdev, soc);
	if (err < 0) {
		tegra_cvb_remove_opp_table(soc->dev, soc->cvb, soc->max_freq);
		return err;
	}

	return 0;
}