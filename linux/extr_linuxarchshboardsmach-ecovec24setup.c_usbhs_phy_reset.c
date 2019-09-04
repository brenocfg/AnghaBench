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
 int /*<<< orphan*/  GPIO_PTB3 ; 
 int /*<<< orphan*/  GPIO_PTB5 ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbhs_phy_reset(struct platform_device *pdev)
{
	/* enable vbus if HOST */
	if (!gpio_get_value(GPIO_PTB3))
		gpio_set_value(GPIO_PTB5, 1);

	return 0;
}