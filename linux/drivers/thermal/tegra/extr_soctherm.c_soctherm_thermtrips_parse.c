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
typedef  scalar_t__ u32 ;
struct tsensor_group_thermtrips {scalar_t__ temp; scalar_t__ id; } ;
struct tegra_soctherm {TYPE_1__* soc; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int num_ttgs; struct tsensor_group_thermtrips* thermtrips; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TEGRA124_SOCTHERM_SENSOR_NUM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra_soctherm* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__* devm_kcalloc (struct device*,int const,int,int /*<<< orphan*/ ) ; 
 int min (int const,int) ; 
 int of_property_count_u32_elems (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32_array (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 

__attribute__((used)) static int soctherm_thermtrips_parse(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct tegra_soctherm *ts = dev_get_drvdata(dev);
	struct tsensor_group_thermtrips *tt = ts->soc->thermtrips;
	const int max_num_prop = ts->soc->num_ttgs * 2;
	u32 *tlb;
	int i, j, n, ret;

	if (!tt)
		return -ENOMEM;

	n = of_property_count_u32_elems(dev->of_node, "nvidia,thermtrips");
	if (n <= 0) {
		dev_info(dev,
			 "missing thermtrips, will use critical trips as shut down temp\n");
		return n;
	}

	n = min(max_num_prop, n);

	tlb = devm_kcalloc(&pdev->dev, max_num_prop, sizeof(u32), GFP_KERNEL);
	if (!tlb)
		return -ENOMEM;
	ret = of_property_read_u32_array(dev->of_node, "nvidia,thermtrips",
					 tlb, n);
	if (ret) {
		dev_err(dev, "invalid num ele: thermtrips:%d\n", ret);
		return ret;
	}

	i = 0;
	for (j = 0; j < n; j = j + 2) {
		if (tlb[j] >= TEGRA124_SOCTHERM_SENSOR_NUM)
			continue;

		tt[i].id = tlb[j];
		tt[i].temp = tlb[j + 1];
		i++;
	}

	return 0;
}