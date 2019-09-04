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
struct tegra_gpio_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MSK_CNF (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  tegra_gpio_mask_write (struct tegra_gpio_info*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_gpio_disable(struct tegra_gpio_info *tgi, unsigned int gpio)
{
	tegra_gpio_mask_write(tgi, GPIO_MSK_CNF(tgi, gpio), gpio, 0);
}