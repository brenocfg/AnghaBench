#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; } ;
struct chv_pinctrl {TYPE_4__* community; int /*<<< orphan*/  pctldev; TYPE_2__ pctldesc; int /*<<< orphan*/  regs; int /*<<< orphan*/  saved_pin_context; int /*<<< orphan*/ * dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  unique_id; } ;
struct acpi_device {int /*<<< orphan*/  handle; TYPE_1__ pnp; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_8__ {int /*<<< orphan*/  acpi_space_id; int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ARRAY_SIZE (TYPE_4__**) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_install_address_space_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct chv_pinctrl*) ; 
 TYPE_4__** chv_communities ; 
 int chv_gpio_probe (struct chv_pinctrl*,int) ; 
 TYPE_2__ chv_pinctrl_desc ; 
 int /*<<< orphan*/  chv_pinctrl_mmio_access_handler ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct chv_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,TYPE_2__*,struct chv_pinctrl*) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct chv_pinctrl*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chv_pinctrl_probe(struct platform_device *pdev)
{
	struct chv_pinctrl *pctrl;
	struct acpi_device *adev;
	acpi_status status;
	int ret, irq, i;

	adev = ACPI_COMPANION(&pdev->dev);
	if (!adev)
		return -ENODEV;

	pctrl = devm_kzalloc(&pdev->dev, sizeof(*pctrl), GFP_KERNEL);
	if (!pctrl)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(chv_communities); i++)
		if (!strcmp(adev->pnp.unique_id, chv_communities[i]->uid)) {
			pctrl->community = chv_communities[i];
			break;
		}
	if (i == ARRAY_SIZE(chv_communities))
		return -ENODEV;

	pctrl->dev = &pdev->dev;

#ifdef CONFIG_PM_SLEEP
	pctrl->saved_pin_context = devm_kcalloc(pctrl->dev,
		pctrl->community->npins, sizeof(*pctrl->saved_pin_context),
		GFP_KERNEL);
	if (!pctrl->saved_pin_context)
		return -ENOMEM;
#endif

	pctrl->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(pctrl->regs))
		return PTR_ERR(pctrl->regs);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	pctrl->pctldesc = chv_pinctrl_desc;
	pctrl->pctldesc.name = dev_name(&pdev->dev);
	pctrl->pctldesc.pins = pctrl->community->pins;
	pctrl->pctldesc.npins = pctrl->community->npins;

	pctrl->pctldev = devm_pinctrl_register(&pdev->dev, &pctrl->pctldesc,
					       pctrl);
	if (IS_ERR(pctrl->pctldev)) {
		dev_err(&pdev->dev, "failed to register pinctrl driver\n");
		return PTR_ERR(pctrl->pctldev);
	}

	ret = chv_gpio_probe(pctrl, irq);
	if (ret)
		return ret;

	status = acpi_install_address_space_handler(adev->handle,
					pctrl->community->acpi_space_id,
					chv_pinctrl_mmio_access_handler,
					NULL, pctrl);
	if (ACPI_FAILURE(status))
		dev_err(&pdev->dev, "failed to install ACPI addr space handler\n");

	platform_set_drvdata(pdev, pctrl);

	return 0;
}