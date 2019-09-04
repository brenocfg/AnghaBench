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
struct spmi_device {int usid; int /*<<< orphan*/  dev; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int devm_of_platform_populate (int /*<<< orphan*/ *) ; 
 struct regmap* devm_regmap_init_spmi_ext (struct spmi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmic_spmi_show_revid (struct regmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spmi_regmap_config ; 

__attribute__((used)) static int pmic_spmi_probe(struct spmi_device *sdev)
{
	struct regmap *regmap;

	regmap = devm_regmap_init_spmi_ext(sdev, &spmi_regmap_config);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	/* Only the first slave id for a PMIC contains this information */
	if (sdev->usid % 2 == 0)
		pmic_spmi_show_revid(regmap, &sdev->dev);

	return devm_of_platform_populate(&sdev->dev);
}