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

/* Variables and functions */
 int /*<<< orphan*/  expstate_chip ; 
 int gpiochip_add_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  impwire_chip ; 

__attribute__((used)) static int xtensa_gpio_probe(struct platform_device *pdev)
{
	int ret;

	ret = gpiochip_add_data(&impwire_chip, NULL);
	if (ret)
		return ret;
	return gpiochip_add_data(&expstate_chip, NULL);
}