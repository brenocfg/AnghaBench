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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * halt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/ * halt_node ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_get_gpio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 TYPE_1__ ppc_md ; 

__attribute__((used)) static int gpio_halt_remove(struct platform_device *pdev)
{
	if (halt_node) {
		int gpio = of_get_gpio(halt_node, 0);
		int irq = irq_of_parse_and_map(halt_node, 0);

		free_irq(irq, halt_node);

		ppc_md.halt = NULL;
		pm_power_off = NULL;

		gpio_free(gpio);

		halt_node = NULL;
	}

	return 0;
}