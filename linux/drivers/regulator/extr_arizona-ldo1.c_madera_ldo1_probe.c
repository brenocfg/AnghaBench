#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ldo1; } ;
struct madera {int internal_dcvdd; TYPE_1__ pdata; int /*<<< orphan*/  regmap; } ;
struct arizona_ldo1 {int /*<<< orphan*/  init_data; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int arizona_ldo1_common_init (struct platform_device*,struct arizona_ldo1*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arizona_ldo1* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_ldo1 ; 
 int /*<<< orphan*/  madera_ldo1_default ; 

__attribute__((used)) static int madera_ldo1_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct arizona_ldo1 *ldo1;
	bool external_dcvdd;
	int ret;

	ldo1 = devm_kzalloc(&pdev->dev, sizeof(*ldo1), GFP_KERNEL);
	if (!ldo1)
		return -ENOMEM;

	ldo1->regmap = madera->regmap;

	ldo1->init_data = madera_ldo1_default;

	ret = arizona_ldo1_common_init(pdev, ldo1, &madera_ldo1,
				       &madera->pdata.ldo1,
				       &external_dcvdd);
	if (ret)
		return ret;

	madera->internal_dcvdd = !external_dcvdd;

	return 0;
}