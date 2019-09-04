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
struct brcmstb_gpio_priv {TYPE_1__* pdev; int /*<<< orphan*/  parent_wake_irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int disable_irq_wake (int /*<<< orphan*/ ) ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmstb_gpio_priv_set_wake(struct brcmstb_gpio_priv *priv,
		unsigned int enable)
{
	int ret = 0;

	if (enable)
		ret = enable_irq_wake(priv->parent_wake_irq);
	else
		ret = disable_irq_wake(priv->parent_wake_irq);
	if (ret)
		dev_err(&priv->pdev->dev, "failed to %s wake-up interrupt\n",
				enable ? "enable" : "disable");
	return ret;
}