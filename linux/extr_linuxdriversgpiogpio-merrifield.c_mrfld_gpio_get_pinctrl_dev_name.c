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

/* Variables and functions */
 char* acpi_dev_get_first_match_name (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static const char *mrfld_gpio_get_pinctrl_dev_name(void)
{
	const char *dev_name = acpi_dev_get_first_match_name("INTC1002", NULL, -1);
	return dev_name ? dev_name : "pinctrl-merrifield";
}