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
struct cbus_host {int /*<<< orphan*/  clk_gpio; int /*<<< orphan*/  dat_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cbus_send_bit(struct cbus_host *host, unsigned bit)
{
	gpio_set_value(host->dat_gpio, bit ? 1 : 0);
	gpio_set_value(host->clk_gpio, 1);
	gpio_set_value(host->clk_gpio, 0);
}