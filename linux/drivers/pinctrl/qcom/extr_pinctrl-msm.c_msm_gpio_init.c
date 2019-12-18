#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct gpio_irq_chip {int num_parents; int /*<<< orphan*/ * parents; int /*<<< orphan*/  handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  parent_handler; TYPE_2__* chip; } ;
struct gpio_chip {int base; unsigned int ngpio; struct gpio_irq_chip irq; int /*<<< orphan*/  init_valid_mask; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; TYPE_3__* parent; int /*<<< orphan*/  label; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  irq_release_resources; int /*<<< orphan*/  irq_request_resources; int /*<<< orphan*/  irq_set_wake; int /*<<< orphan*/  irq_set_type; int /*<<< orphan*/  irq_ack; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  irq_enable; } ;
struct msm_pinctrl {struct gpio_chip chip; TYPE_3__* dev; int /*<<< orphan*/  irq; TYPE_2__ irq_chip; TYPE_1__* soc; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {unsigned int ngpios; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 unsigned int MAX_NR_GPIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/ * devm_kcalloc (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (struct gpio_chip*,struct msm_pinctrl*) ; 
 int gpiochip_add_pin_range (struct gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gpiochip_remove (struct gpio_chip*) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  msm_gpio_init_valid_mask ; 
 int /*<<< orphan*/  msm_gpio_irq_ack ; 
 int /*<<< orphan*/  msm_gpio_irq_enable ; 
 int /*<<< orphan*/  msm_gpio_irq_handler ; 
 int /*<<< orphan*/  msm_gpio_irq_mask ; 
 int /*<<< orphan*/  msm_gpio_irq_relres ; 
 int /*<<< orphan*/  msm_gpio_irq_reqres ; 
 int /*<<< orphan*/  msm_gpio_irq_set_type ; 
 int /*<<< orphan*/  msm_gpio_irq_set_wake ; 
 int /*<<< orphan*/  msm_gpio_irq_unmask ; 
 scalar_t__ msm_gpio_needs_valid_mask (struct msm_pinctrl*) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int msm_gpio_init(struct msm_pinctrl *pctrl)
{
	struct gpio_chip *chip;
	struct gpio_irq_chip *girq;
	int ret;
	unsigned ngpio = pctrl->soc->ngpios;

	if (WARN_ON(ngpio > MAX_NR_GPIO))
		return -EINVAL;

	chip = &pctrl->chip;
	chip->base = -1;
	chip->ngpio = ngpio;
	chip->label = dev_name(pctrl->dev);
	chip->parent = pctrl->dev;
	chip->owner = THIS_MODULE;
	chip->of_node = pctrl->dev->of_node;
	if (msm_gpio_needs_valid_mask(pctrl))
		chip->init_valid_mask = msm_gpio_init_valid_mask;

	pctrl->irq_chip.name = "msmgpio";
	pctrl->irq_chip.irq_enable = msm_gpio_irq_enable;
	pctrl->irq_chip.irq_mask = msm_gpio_irq_mask;
	pctrl->irq_chip.irq_unmask = msm_gpio_irq_unmask;
	pctrl->irq_chip.irq_ack = msm_gpio_irq_ack;
	pctrl->irq_chip.irq_set_type = msm_gpio_irq_set_type;
	pctrl->irq_chip.irq_set_wake = msm_gpio_irq_set_wake;
	pctrl->irq_chip.irq_request_resources = msm_gpio_irq_reqres;
	pctrl->irq_chip.irq_release_resources = msm_gpio_irq_relres;

	girq = &chip->irq;
	girq->chip = &pctrl->irq_chip;
	girq->parent_handler = msm_gpio_irq_handler;
	girq->num_parents = 1;
	girq->parents = devm_kcalloc(pctrl->dev, 1, sizeof(*girq->parents),
				     GFP_KERNEL);
	if (!girq->parents)
		return -ENOMEM;
	girq->default_type = IRQ_TYPE_NONE;
	girq->handler = handle_bad_irq;
	girq->parents[0] = pctrl->irq;

	ret = gpiochip_add_data(&pctrl->chip, pctrl);
	if (ret) {
		dev_err(pctrl->dev, "Failed register gpiochip\n");
		return ret;
	}

	/*
	 * For DeviceTree-supported systems, the gpio core checks the
	 * pinctrl's device node for the "gpio-ranges" property.
	 * If it is present, it takes care of adding the pin ranges
	 * for the driver. In this case the driver can skip ahead.
	 *
	 * In order to remain compatible with older, existing DeviceTree
	 * files which don't set the "gpio-ranges" property or systems that
	 * utilize ACPI the driver has to call gpiochip_add_pin_range().
	 */
	if (!of_property_read_bool(pctrl->dev->of_node, "gpio-ranges")) {
		ret = gpiochip_add_pin_range(&pctrl->chip,
			dev_name(pctrl->dev), 0, 0, chip->ngpio);
		if (ret) {
			dev_err(pctrl->dev, "Failed to add pin range\n");
			gpiochip_remove(&pctrl->chip);
			return ret;
		}
	}

	return 0;
}