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
struct pmic_gpio_state {int /*<<< orphan*/  chip; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct pmic_gpio_state* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pmic_gpio_remove(struct platform_device *pdev)
{
	struct pmic_gpio_state *state = platform_get_drvdata(pdev);

	gpiochip_remove(&state->chip);
	return 0;
}