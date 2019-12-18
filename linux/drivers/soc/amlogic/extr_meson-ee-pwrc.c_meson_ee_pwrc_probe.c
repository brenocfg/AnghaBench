#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct meson_ee_pwrc_domain_data {int count; int /*<<< orphan*/ * domains; } ;
struct meson_ee_pwrc_domain {int /*<<< orphan*/  base; int /*<<< orphan*/  desc; } ;
struct TYPE_6__ {int num_domains; int /*<<< orphan*/ ** domains; } ;
struct meson_ee_pwrc {TYPE_1__ xlate; struct meson_ee_pwrc_domain* domains; struct regmap* regmap_hhi; struct regmap* regmap_ao; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 void* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct meson_ee_pwrc* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int meson_ee_pwrc_init_domain (struct platform_device*,struct meson_ee_pwrc*,struct meson_ee_pwrc_domain*) ; 
 struct meson_ee_pwrc_domain_data* of_device_get_match_data (TYPE_2__*) ; 
 int /*<<< orphan*/  of_genpd_add_provider_onecell (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_ee_pwrc*) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int meson_ee_pwrc_probe(struct platform_device *pdev)
{
	const struct meson_ee_pwrc_domain_data *match;
	struct regmap *regmap_ao, *regmap_hhi;
	struct meson_ee_pwrc *pwrc;
	int i, ret;

	match = of_device_get_match_data(&pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "failed to get match data\n");
		return -ENODEV;
	}

	pwrc = devm_kzalloc(&pdev->dev, sizeof(*pwrc), GFP_KERNEL);
	if (!pwrc)
		return -ENOMEM;

	pwrc->xlate.domains = devm_kcalloc(&pdev->dev, match->count,
					   sizeof(*pwrc->xlate.domains),
					   GFP_KERNEL);
	if (!pwrc->xlate.domains)
		return -ENOMEM;

	pwrc->domains = devm_kcalloc(&pdev->dev, match->count,
				     sizeof(*pwrc->domains), GFP_KERNEL);
	if (!pwrc->domains)
		return -ENOMEM;

	pwrc->xlate.num_domains = match->count;

	regmap_hhi = syscon_node_to_regmap(of_get_parent(pdev->dev.of_node));
	if (IS_ERR(regmap_hhi)) {
		dev_err(&pdev->dev, "failed to get HHI regmap\n");
		return PTR_ERR(regmap_hhi);
	}

	regmap_ao = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						    "amlogic,ao-sysctrl");
	if (IS_ERR(regmap_ao)) {
		dev_err(&pdev->dev, "failed to get AO regmap\n");
		return PTR_ERR(regmap_ao);
	}

	pwrc->regmap_ao = regmap_ao;
	pwrc->regmap_hhi = regmap_hhi;

	platform_set_drvdata(pdev, pwrc);

	for (i = 0 ; i < match->count ; ++i) {
		struct meson_ee_pwrc_domain *dom = &pwrc->domains[i];

		memcpy(&dom->desc, &match->domains[i], sizeof(dom->desc));

		ret = meson_ee_pwrc_init_domain(pdev, pwrc, dom);
		if (ret)
			return ret;

		pwrc->xlate.domains[i] = &dom->base;
	}

	of_genpd_add_provider_onecell(pdev->dev.of_node, &pwrc->xlate);

	return 0;
}