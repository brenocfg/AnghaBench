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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct mipi_phy_device_desc {unsigned int num_regmaps; unsigned int num_phys; int /*<<< orphan*/ * phys; int /*<<< orphan*/ * regmap_names; } ;
struct exynos_mipi_video_phy {unsigned int num_phys; TYPE_1__* phys; int /*<<< orphan*/  slock; struct phy** regmaps; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {unsigned int index; int /*<<< orphan*/ * data; struct phy* phy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct exynos_mipi_video_phy*) ; 
 struct exynos_mipi_video_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exynos_mipi_video_phy_ops ; 
 int /*<<< orphan*/  exynos_mipi_video_phy_xlate ; 
 struct mipi_phy_device_desc* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct phy* syscon_regmap_lookup_by_phandle (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_mipi_video_phy_probe(struct platform_device *pdev)
{
	const struct mipi_phy_device_desc *phy_dev;
	struct exynos_mipi_video_phy *state;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct phy_provider *phy_provider;
	unsigned int i;

	phy_dev = of_device_get_match_data(dev);
	if (!phy_dev)
		return -ENODEV;

	state = devm_kzalloc(dev, sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	for (i = 0; i < phy_dev->num_regmaps; i++) {
		state->regmaps[i] = syscon_regmap_lookup_by_phandle(np,
						phy_dev->regmap_names[i]);
		if (IS_ERR(state->regmaps[i]))
			return PTR_ERR(state->regmaps[i]);
	}
	state->num_phys = phy_dev->num_phys;
	spin_lock_init(&state->slock);

	dev_set_drvdata(dev, state);

	for (i = 0; i < state->num_phys; i++) {
		struct phy *phy = devm_phy_create(dev, NULL,
						  &exynos_mipi_video_phy_ops);
		if (IS_ERR(phy)) {
			dev_err(dev, "failed to create PHY %d\n", i);
			return PTR_ERR(phy);
		}

		state->phys[i].phy = phy;
		state->phys[i].index = i;
		state->phys[i].data = &phy_dev->phys[i];
		phy_set_drvdata(phy, &state->phys[i]);
	}

	phy_provider = devm_of_phy_provider_register(dev,
					exynos_mipi_video_phy_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}