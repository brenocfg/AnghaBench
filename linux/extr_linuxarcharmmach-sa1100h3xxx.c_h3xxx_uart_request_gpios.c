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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int gpio_request_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h3xxx_uart_gpio ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static bool h3xxx_uart_request_gpios(void)
{
	static bool h3xxx_uart_gpio_ok;
	int rc;

	if (h3xxx_uart_gpio_ok)
		return true;

	rc = gpio_request_array(h3xxx_uart_gpio, ARRAY_SIZE(h3xxx_uart_gpio));
	if (rc)
		pr_err("h3xxx_uart_request_gpios: error %d\n", rc);
	else
		h3xxx_uart_gpio_ok = true;

	return h3xxx_uart_gpio_ok;
}