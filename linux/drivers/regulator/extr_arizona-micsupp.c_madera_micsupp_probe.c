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
struct TYPE_3__ {int /*<<< orphan*/  micvdd; } ;
struct madera {TYPE_1__ pdata; int /*<<< orphan*/  dev; int /*<<< orphan*/  dapm; int /*<<< orphan*/  regmap; } ;
struct arizona_micsupp {int /*<<< orphan*/  init_data; int /*<<< orphan*/  dev; int /*<<< orphan*/ * dapm; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int arizona_micsupp_common_init (struct platform_device*,struct arizona_micsupp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arizona_micsupp_ext_default ; 
 struct madera* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct arizona_micsupp* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  madera_micsupp ; 

__attribute__((used)) static int madera_micsupp_probe(struct platform_device *pdev)
{
	struct madera *madera = dev_get_drvdata(pdev->dev.parent);
	struct arizona_micsupp *micsupp;

	micsupp = devm_kzalloc(&pdev->dev, sizeof(*micsupp), GFP_KERNEL);
	if (!micsupp)
		return -ENOMEM;

	micsupp->regmap = madera->regmap;
	micsupp->dapm = &madera->dapm;
	micsupp->dev = madera->dev;
	micsupp->init_data = arizona_micsupp_ext_default;

	return arizona_micsupp_common_init(pdev, micsupp, &madera_micsupp,
					   &madera->pdata.micvdd);
}