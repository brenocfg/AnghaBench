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
struct exynos_dsi {int te_gpio; int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  IRQ_NOAUTOEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exynos_dsi_te_irq_handler ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int gpio_request (int,char*) ; 
 int gpio_to_irq (int) ; 
 int /*<<< orphan*/  irq_set_status_flags (int,int /*<<< orphan*/ ) ; 
 int of_get_named_gpio (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct exynos_dsi*) ; 

__attribute__((used)) static int exynos_dsi_register_te_irq(struct exynos_dsi *dsi,
				      struct device *panel)
{
	int ret;
	int te_gpio_irq;

	dsi->te_gpio = of_get_named_gpio(panel->of_node, "te-gpios", 0);
	if (dsi->te_gpio == -ENOENT)
		return 0;

	if (!gpio_is_valid(dsi->te_gpio)) {
		ret = dsi->te_gpio;
		dev_err(dsi->dev, "cannot get te-gpios, %d\n", ret);
		goto out;
	}

	ret = gpio_request(dsi->te_gpio, "te_gpio");
	if (ret) {
		dev_err(dsi->dev, "gpio request failed with %d\n", ret);
		goto out;
	}

	te_gpio_irq = gpio_to_irq(dsi->te_gpio);
	irq_set_status_flags(te_gpio_irq, IRQ_NOAUTOEN);

	ret = request_threaded_irq(te_gpio_irq, exynos_dsi_te_irq_handler, NULL,
					IRQF_TRIGGER_RISING, "TE", dsi);
	if (ret) {
		dev_err(dsi->dev, "request interrupt failed with %d\n", ret);
		gpio_free(dsi->te_gpio);
		goto out;
	}

out:
	return ret;
}