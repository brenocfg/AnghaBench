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
struct platform_device {int dummy; } ;
struct pcf50633_mbc {int /*<<< orphan*/  ac; int /*<<< orphan*/  adapter; int /*<<< orphan*/  usb; int /*<<< orphan*/  pcf; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbc_irq_handlers ; 
 int /*<<< orphan*/  pcf50633_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcf50633_mbc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf50633_mbc_remove(struct platform_device *pdev)
{
	struct pcf50633_mbc *mbc = platform_get_drvdata(pdev);
	int i;

	/* Remove IRQ handlers */
	for (i = 0; i < ARRAY_SIZE(mbc_irq_handlers); i++)
		pcf50633_free_irq(mbc->pcf, mbc_irq_handlers[i]);

	power_supply_unregister(mbc->usb);
	power_supply_unregister(mbc->adapter);
	power_supply_unregister(mbc->ac);

	return 0;
}