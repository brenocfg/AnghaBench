#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct of_phandle_args {int args_count; int* args; } ;
struct gpio_chip {int of_gpio_n_cells; int base; int ngpio; } ;
struct brcmstb_gpio_priv {int gpio_base; TYPE_1__* pdev; } ;
struct brcmstb_gpio_bank {int width; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 struct brcmstb_gpio_priv* brcmstb_gpio_gc_to_priv (struct gpio_chip*) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*,int) ; 
 struct brcmstb_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int brcmstb_gpio_of_xlate(struct gpio_chip *gc,
		const struct of_phandle_args *gpiospec, u32 *flags)
{
	struct brcmstb_gpio_priv *priv = brcmstb_gpio_gc_to_priv(gc);
	struct brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	int offset;

	if (gc->of_gpio_n_cells != 2) {
		WARN_ON(1);
		return -EINVAL;
	}

	if (WARN_ON(gpiospec->args_count < gc->of_gpio_n_cells))
		return -EINVAL;

	offset = gpiospec->args[0] - (gc->base - priv->gpio_base);
	if (offset >= gc->ngpio || offset < 0)
		return -EINVAL;

	if (unlikely(offset >= bank->width)) {
		dev_warn_ratelimited(&priv->pdev->dev,
			"Received request for invalid GPIO offset %d\n",
			gpiospec->args[0]);
	}

	if (flags)
		*flags = gpiospec->args[1];

	return offset;
}