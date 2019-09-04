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
struct spear_sdhci {int card_int_gpio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_probe_config_dt(struct device_node *np,
				struct spear_sdhci *host)
{
	int cd_gpio;

	cd_gpio = of_get_named_gpio(np, "cd-gpios", 0);
	if (!gpio_is_valid(cd_gpio))
		cd_gpio = -1;

	host->card_int_gpio = cd_gpio;
}