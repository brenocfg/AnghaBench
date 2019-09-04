#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tegra_bpmp {int dummy; } ;
struct tegra186_cpufreq_data {unsigned int num_clusters; struct tegra186_cpufreq_cluster* clusters; struct tegra_bpmp* regs; } ;
struct tegra186_cpufreq_cluster {struct tegra_bpmp* table; TYPE_2__* info; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  bpmp_cluster_id; } ;
struct TYPE_5__ {struct tegra186_cpufreq_data* driver_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct tegra_bpmp*) ; 
 int PTR_ERR (struct tegra_bpmp*) ; 
 unsigned int cpufreq_register_driver (TYPE_1__*) ; 
 struct tegra_bpmp* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra186_cpufreq_cluster* devm_kcalloc (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct tegra186_cpufreq_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct tegra_bpmp* init_vhint_table (struct platform_device*,struct tegra_bpmp*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tegra186_clusters ; 
 TYPE_1__ tegra186_cpufreq_driver ; 
 struct tegra_bpmp* tegra_bpmp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_bpmp_put (struct tegra_bpmp*) ; 

__attribute__((used)) static int tegra186_cpufreq_probe(struct platform_device *pdev)
{
	struct tegra186_cpufreq_data *data;
	struct tegra_bpmp *bpmp;
	struct resource *res;
	unsigned int i = 0, err;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->clusters = devm_kcalloc(&pdev->dev, ARRAY_SIZE(tegra186_clusters),
				      sizeof(*data->clusters), GFP_KERNEL);
	if (!data->clusters)
		return -ENOMEM;

	data->num_clusters = ARRAY_SIZE(tegra186_clusters);

	bpmp = tegra_bpmp_get(&pdev->dev);
	if (IS_ERR(bpmp))
		return PTR_ERR(bpmp);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(data->regs)) {
		err = PTR_ERR(data->regs);
		goto put_bpmp;
	}

	for (i = 0; i < data->num_clusters; i++) {
		struct tegra186_cpufreq_cluster *cluster = &data->clusters[i];

		cluster->info = &tegra186_clusters[i];
		cluster->table = init_vhint_table(
			pdev, bpmp, cluster->info->bpmp_cluster_id);
		if (IS_ERR(cluster->table)) {
			err = PTR_ERR(cluster->table);
			goto put_bpmp;
		}
	}

	tegra_bpmp_put(bpmp);

	tegra186_cpufreq_driver.driver_data = data;

	err = cpufreq_register_driver(&tegra186_cpufreq_driver);
	if (err)
		return err;

	return 0;

put_bpmp:
	tegra_bpmp_put(bpmp);

	return err;
}