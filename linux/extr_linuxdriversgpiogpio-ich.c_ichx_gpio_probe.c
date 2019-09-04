#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct lpc_ich_info {int gpio_version; int /*<<< orphan*/  use_gpio; } ;
struct TYPE_14__ {scalar_t__ ngpio; scalar_t__ base; } ;
struct TYPE_13__ {TYPE_3__ chip; struct resource* pm_base; TYPE_1__* desc; struct resource* gpio_base; int /*<<< orphan*/  use_gpio; int /*<<< orphan*/  lock; struct platform_device* dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  uses_gpe0; } ;

/* Variables and functions */
#define  AVOTON_GPIO 135 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
#define  ICH_I3100_GPIO 134 
 int /*<<< orphan*/  ICH_RES_GPE0 ; 
 int /*<<< orphan*/  ICH_RES_GPIO ; 
#define  ICH_V10CONS_GPIO 133 
#define  ICH_V10CORP_GPIO 132 
#define  ICH_V5_GPIO 131 
#define  ICH_V6_GPIO 130 
#define  ICH_V7_GPIO 129 
#define  ICH_V9_GPIO 128 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 TYPE_1__ avoton_desc ; 
 struct lpc_ich_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_request_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ i3100_desc ; 
 TYPE_1__ ich10_cons_desc ; 
 TYPE_1__ ich10_corp_desc ; 
 TYPE_1__ ich6_desc ; 
 TYPE_1__ ich7_desc ; 
 TYPE_1__ ich9_desc ; 
 int ichx_gpio_request_regions (int /*<<< orphan*/ *,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ichx_gpiolib_setup (TYPE_3__*) ; 
 TYPE_2__ ichx_priv ; 
 TYPE_1__ intel5_desc ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ichx_gpio_probe(struct platform_device *pdev)
{
	struct resource *res_base, *res_pm;
	int err;
	struct lpc_ich_info *ich_info = dev_get_platdata(&pdev->dev);

	if (!ich_info)
		return -ENODEV;

	ichx_priv.dev = pdev;

	switch (ich_info->gpio_version) {
	case ICH_I3100_GPIO:
		ichx_priv.desc = &i3100_desc;
		break;
	case ICH_V5_GPIO:
		ichx_priv.desc = &intel5_desc;
		break;
	case ICH_V6_GPIO:
		ichx_priv.desc = &ich6_desc;
		break;
	case ICH_V7_GPIO:
		ichx_priv.desc = &ich7_desc;
		break;
	case ICH_V9_GPIO:
		ichx_priv.desc = &ich9_desc;
		break;
	case ICH_V10CORP_GPIO:
		ichx_priv.desc = &ich10_corp_desc;
		break;
	case ICH_V10CONS_GPIO:
		ichx_priv.desc = &ich10_cons_desc;
		break;
	case AVOTON_GPIO:
		ichx_priv.desc = &avoton_desc;
		break;
	default:
		return -ENODEV;
	}

	spin_lock_init(&ichx_priv.lock);
	res_base = platform_get_resource(pdev, IORESOURCE_IO, ICH_RES_GPIO);
	ichx_priv.use_gpio = ich_info->use_gpio;
	err = ichx_gpio_request_regions(&pdev->dev, res_base, pdev->name,
					ichx_priv.use_gpio);
	if (err)
		return err;

	ichx_priv.gpio_base = res_base;

	/*
	 * If necessary, determine the I/O address of ACPI/power management
	 * registers which are needed to read the the GPE0 register for GPI pins
	 * 0 - 15 on some chipsets.
	 */
	if (!ichx_priv.desc->uses_gpe0)
		goto init;

	res_pm = platform_get_resource(pdev, IORESOURCE_IO, ICH_RES_GPE0);
	if (!res_pm) {
		pr_warn("ACPI BAR is unavailable, GPI 0 - 15 unavailable\n");
		goto init;
	}

	if (!devm_request_region(&pdev->dev, res_pm->start,
			resource_size(res_pm), pdev->name)) {
		pr_warn("ACPI BAR is busy, GPI 0 - 15 unavailable\n");
		goto init;
	}

	ichx_priv.pm_base = res_pm;

init:
	ichx_gpiolib_setup(&ichx_priv.chip);
	err = gpiochip_add_data(&ichx_priv.chip, NULL);
	if (err) {
		pr_err("Failed to register GPIOs\n");
		return err;
	}

	pr_info("GPIO from %d to %d on %s\n", ichx_priv.chip.base,
	       ichx_priv.chip.base + ichx_priv.chip.ngpio - 1, DRV_NAME);

	return 0;
}