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
struct resource {int /*<<< orphan*/  start; } ;
struct power_supply_config {struct goldfish_battery_data* drv_data; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct goldfish_battery_data {scalar_t__ irq; void* battery; void* ac; int /*<<< orphan*/ * reg_base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATTERY_INT_ENABLE ; 
 int /*<<< orphan*/  BATTERY_INT_MASK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GOLDFISH_BATTERY_WRITE (struct goldfish_battery_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ac_desc ; 
 int /*<<< orphan*/  battery_desc ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct goldfish_battery_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct goldfish_battery_data*) ; 
 int /*<<< orphan*/  goldfish_battery_interrupt ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct goldfish_battery_data*) ; 
 void* power_supply_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (void*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int goldfish_battery_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *r;
	struct goldfish_battery_data *data;
	struct power_supply_config psy_cfg = {};

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (data == NULL)
		return -ENOMEM;

	spin_lock_init(&data->lock);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (r == NULL) {
		dev_err(&pdev->dev, "platform_get_resource failed\n");
		return -ENODEV;
	}

	data->reg_base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	if (data->reg_base == NULL) {
		dev_err(&pdev->dev, "unable to remap MMIO\n");
		return -ENOMEM;
	}

	data->irq = platform_get_irq(pdev, 0);
	if (data->irq < 0) {
		dev_err(&pdev->dev, "platform_get_irq failed\n");
		return -ENODEV;
	}

	ret = devm_request_irq(&pdev->dev, data->irq,
			       goldfish_battery_interrupt,
			       IRQF_SHARED, pdev->name, data);
	if (ret)
		return ret;

	psy_cfg.drv_data = data;

	data->ac = power_supply_register(&pdev->dev, &ac_desc, &psy_cfg);
	if (IS_ERR(data->ac))
		return PTR_ERR(data->ac);

	data->battery = power_supply_register(&pdev->dev, &battery_desc,
						&psy_cfg);
	if (IS_ERR(data->battery)) {
		power_supply_unregister(data->ac);
		return PTR_ERR(data->battery);
	}

	platform_set_drvdata(pdev, data);

	GOLDFISH_BATTERY_WRITE(data, BATTERY_INT_ENABLE, BATTERY_INT_MASK);
	return 0;
}