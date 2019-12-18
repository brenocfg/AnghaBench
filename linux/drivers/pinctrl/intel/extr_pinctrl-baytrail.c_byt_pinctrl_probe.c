#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_pinctrl_soc_data {int /*<<< orphan*/  uid; } ;
struct TYPE_7__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; } ;
struct byt_gpio {int /*<<< orphan*/  lock; int /*<<< orphan*/  pctl_dev; TYPE_3__ pctl_desc; TYPE_2__* soc_data; struct platform_device* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  unique_id; } ;
struct acpi_device {TYPE_1__ pnp; } ;
struct TYPE_6__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int byt_gpio_probe (struct byt_gpio*) ; 
 TYPE_3__ byt_pinctrl_desc ; 
 int byt_set_soc_data (struct byt_gpio*,struct intel_pinctrl_soc_data const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_match_data (int /*<<< orphan*/ *) ; 
 struct byt_gpio* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,TYPE_3__*,struct byt_gpio*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct byt_gpio*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_pinctrl_probe(struct platform_device *pdev)
{
	const struct intel_pinctrl_soc_data *soc_data = NULL;
	const struct intel_pinctrl_soc_data **soc_table;
	struct acpi_device *acpi_dev;
	struct byt_gpio *vg;
	int i, ret;

	acpi_dev = ACPI_COMPANION(&pdev->dev);
	if (!acpi_dev)
		return -ENODEV;

	soc_table = (const struct intel_pinctrl_soc_data **)device_get_match_data(&pdev->dev);

	for (i = 0; soc_table[i]; i++) {
		if (!strcmp(acpi_dev->pnp.unique_id, soc_table[i]->uid)) {
			soc_data = soc_table[i];
			break;
		}
	}

	if (!soc_data)
		return -ENODEV;

	vg = devm_kzalloc(&pdev->dev, sizeof(*vg), GFP_KERNEL);
	if (!vg)
		return -ENOMEM;

	vg->pdev = pdev;
	ret = byt_set_soc_data(vg, soc_data);
	if (ret) {
		dev_err(&pdev->dev, "failed to set soc data\n");
		return ret;
	}

	vg->pctl_desc		= byt_pinctrl_desc;
	vg->pctl_desc.name	= dev_name(&pdev->dev);
	vg->pctl_desc.pins	= vg->soc_data->pins;
	vg->pctl_desc.npins	= vg->soc_data->npins;

	vg->pctl_dev = devm_pinctrl_register(&pdev->dev, &vg->pctl_desc, vg);
	if (IS_ERR(vg->pctl_dev)) {
		dev_err(&pdev->dev, "failed to register pinctrl driver\n");
		return PTR_ERR(vg->pctl_dev);
	}

	raw_spin_lock_init(&vg->lock);

	ret = byt_gpio_probe(vg);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, vg);
	pm_runtime_enable(&pdev->dev);

	return 0;
}