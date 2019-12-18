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
struct lpc32xx_nand_host {TYPE_1__* ncfg; } ;
struct TYPE_2__ {int /*<<< orphan*/  wp_gpio; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpc32xx_wp_disable(struct lpc32xx_nand_host *host)
{
	if (gpio_is_valid(host->ncfg->wp_gpio))
		gpio_set_value(host->ncfg->wp_gpio, 1);
}