#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_6__ {int ngpio; } ;
struct TYPE_5__ {TYPE_1__* vdev; TYPE_3__ gpio_chip; int /*<<< orphan*/ * active_gpios; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__ viafb_gpio_config ; 
 int /*<<< orphan*/  viafb_gpio_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viafb_gpio_pm_hooks ; 
 int /*<<< orphan*/  viafb_pm_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viafb_gpio_remove(struct platform_device *platdev)
{
	unsigned long flags;
	int i;

#ifdef CONFIG_PM
	viafb_pm_unregister(&viafb_gpio_pm_hooks);
#endif

	/*
	 * Get unregistered.
	 */
	if (viafb_gpio_config.gpio_chip.ngpio > 0) {
		gpiochip_remove(&viafb_gpio_config.gpio_chip);
	}
	/*
	 * Disable the ports.
	 */
	spin_lock_irqsave(&viafb_gpio_config.vdev->reg_lock, flags);
	for (i = 0; i < viafb_gpio_config.gpio_chip.ngpio; i += 2)
		viafb_gpio_disable(viafb_gpio_config.active_gpios[i]);
	viafb_gpio_config.gpio_chip.ngpio = 0;
	spin_unlock_irqrestore(&viafb_gpio_config.vdev->reg_lock, flags);
	return 0;
}