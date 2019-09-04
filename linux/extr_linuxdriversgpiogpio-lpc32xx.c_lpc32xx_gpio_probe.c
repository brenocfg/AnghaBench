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
struct TYPE_7__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_8__ {int of_gpio_n_cells; scalar_t__ of_node; int /*<<< orphan*/  of_xlate; } ;
struct TYPE_6__ {TYPE_3__ chip; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_gpiochip_add_data (TYPE_2__*,TYPE_3__*,TYPE_1__*) ; 
 TYPE_1__* lpc32xx_gpiochip ; 
 int /*<<< orphan*/  lpc32xx_of_xlate ; 

__attribute__((used)) static int lpc32xx_gpio_probe(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(lpc32xx_gpiochip); i++) {
		if (pdev->dev.of_node) {
			lpc32xx_gpiochip[i].chip.of_xlate = lpc32xx_of_xlate;
			lpc32xx_gpiochip[i].chip.of_gpio_n_cells = 3;
			lpc32xx_gpiochip[i].chip.of_node = pdev->dev.of_node;
		}
		devm_gpiochip_add_data(&pdev->dev, &lpc32xx_gpiochip[i].chip,
				  &lpc32xx_gpiochip[i]);
	}

	return 0;
}