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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct omap_gpio_platform_data {int dbck_flag; int loses_context; int /*<<< orphan*/  get_context_loss_count; TYPE_2__* regs; int /*<<< orphan*/  non_wakeup_gpios; scalar_t__ is_mpuio; int /*<<< orphan*/  bank_width; int /*<<< orphan*/  bank_stride; } ;
struct of_device_id {struct omap_gpio_platform_data* data; } ;
struct irq_chip {struct device* parent_device; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  irq_bus_sync_unlock; int /*<<< orphan*/  irq_bus_lock; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_shutdown; int /*<<< orphan*/  irq_startup; } ;
struct TYPE_8__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; struct device* parent; } ;
struct gpio_bank {int irq; int dbck_flag; int loses_context; TYPE_4__ nb; int /*<<< orphan*/  dbck; scalar_t__ is_mpuio; int /*<<< orphan*/  base; int /*<<< orphan*/  wa_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  set_dataout; TYPE_2__* regs; int /*<<< orphan*/  get_context_loss_count; TYPE_1__ chip; int /*<<< orphan*/  non_wakeup_gpios; int /*<<< orphan*/  width; int /*<<< orphan*/  stride; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq_ack; } ;
struct TYPE_6__ {scalar_t__ clr_dataout; scalar_t__ set_dataout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQCHIP_MASK_ON_SUSPEND ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pm_register_notifier (TYPE_4__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct omap_gpio_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_3__ dummy_irq_chip ; 
 int /*<<< orphan*/  gpio_irq_bus_sync_unlock ; 
 int /*<<< orphan*/  gpio_omap_cpu_notifier ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int omap_gpio_chip_init (struct gpio_bank*,struct irq_chip*) ; 
 int /*<<< orphan*/  omap_gpio_irq_bus_lock ; 
 int /*<<< orphan*/  omap_gpio_irq_shutdown ; 
 int /*<<< orphan*/  omap_gpio_irq_startup ; 
 int /*<<< orphan*/  omap_gpio_irq_type ; 
 int /*<<< orphan*/  omap_gpio_mask_irq ; 
 int /*<<< orphan*/  omap_gpio_match ; 
 int /*<<< orphan*/  omap_gpio_mod_init (struct gpio_bank*) ; 
 int /*<<< orphan*/  omap_gpio_show_rev (struct gpio_bank*) ; 
 int /*<<< orphan*/  omap_gpio_unmask_irq ; 
 int /*<<< orphan*/  omap_gpio_wake_enable ; 
 int /*<<< orphan*/  omap_mpuio_init (struct gpio_bank*) ; 
 int /*<<< orphan*/  omap_set_gpio_dataout_mask ; 
 int /*<<< orphan*/  omap_set_gpio_dataout_reg ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct gpio_bank*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	const struct of_device_id *match;
	const struct omap_gpio_platform_data *pdata;
	struct gpio_bank *bank;
	struct irq_chip *irqc;
	int ret;

	match = of_match_device(of_match_ptr(omap_gpio_match), dev);

	pdata = match ? match->data : dev_get_platdata(dev);
	if (!pdata)
		return -EINVAL;

	bank = devm_kzalloc(dev, sizeof(*bank), GFP_KERNEL);
	if (!bank)
		return -ENOMEM;

	irqc = devm_kzalloc(dev, sizeof(*irqc), GFP_KERNEL);
	if (!irqc)
		return -ENOMEM;

	irqc->irq_startup = omap_gpio_irq_startup,
	irqc->irq_shutdown = omap_gpio_irq_shutdown,
	irqc->irq_ack = dummy_irq_chip.irq_ack,
	irqc->irq_mask = omap_gpio_mask_irq,
	irqc->irq_unmask = omap_gpio_unmask_irq,
	irqc->irq_set_type = omap_gpio_irq_type,
	irqc->irq_set_wake = omap_gpio_wake_enable,
	irqc->irq_bus_lock = omap_gpio_irq_bus_lock,
	irqc->irq_bus_sync_unlock = gpio_irq_bus_sync_unlock,
	irqc->name = dev_name(&pdev->dev);
	irqc->flags = IRQCHIP_MASK_ON_SUSPEND;
	irqc->parent_device = dev;

	bank->irq = platform_get_irq(pdev, 0);
	if (bank->irq <= 0) {
		if (!bank->irq)
			bank->irq = -ENXIO;
		if (bank->irq != -EPROBE_DEFER)
			dev_err(dev,
				"can't get irq resource ret=%d\n", bank->irq);
		return bank->irq;
	}

	bank->chip.parent = dev;
	bank->chip.owner = THIS_MODULE;
	bank->dbck_flag = pdata->dbck_flag;
	bank->stride = pdata->bank_stride;
	bank->width = pdata->bank_width;
	bank->is_mpuio = pdata->is_mpuio;
	bank->non_wakeup_gpios = pdata->non_wakeup_gpios;
	bank->regs = pdata->regs;
#ifdef CONFIG_OF_GPIO
	bank->chip.of_node = of_node_get(node);
#endif

	if (node) {
		if (!of_property_read_bool(node, "ti,gpio-always-on"))
			bank->loses_context = true;
	} else {
		bank->loses_context = pdata->loses_context;

		if (bank->loses_context)
			bank->get_context_loss_count =
				pdata->get_context_loss_count;
	}

	if (bank->regs->set_dataout && bank->regs->clr_dataout)
		bank->set_dataout = omap_set_gpio_dataout_reg;
	else
		bank->set_dataout = omap_set_gpio_dataout_mask;

	raw_spin_lock_init(&bank->lock);
	raw_spin_lock_init(&bank->wa_lock);

	/* Static mapping, never released */
	bank->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(bank->base)) {
		return PTR_ERR(bank->base);
	}

	if (bank->dbck_flag) {
		bank->dbck = devm_clk_get(dev, "dbclk");
		if (IS_ERR(bank->dbck)) {
			dev_err(dev,
				"Could not get gpio dbck. Disable debounce\n");
			bank->dbck_flag = false;
		} else {
			clk_prepare(bank->dbck);
		}
	}

	platform_set_drvdata(pdev, bank);

	pm_runtime_enable(dev);
	pm_runtime_get_sync(dev);

	if (bank->is_mpuio)
		omap_mpuio_init(bank);

	omap_gpio_mod_init(bank);

	ret = omap_gpio_chip_init(bank, irqc);
	if (ret) {
		pm_runtime_put_sync(dev);
		pm_runtime_disable(dev);
		if (bank->dbck_flag)
			clk_unprepare(bank->dbck);
		return ret;
	}

	omap_gpio_show_rev(bank);

	bank->nb.notifier_call = gpio_omap_cpu_notifier;
	cpu_pm_register_notifier(&bank->nb);

	pm_runtime_put(dev);

	return 0;
}