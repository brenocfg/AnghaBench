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
struct sdhci_pci_slot {int rst_n_gpio; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int,int) ; 
 struct sdhci_pci_slot* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sdhci_pci_gpio_hw_reset(struct sdhci_host *host)
{
	struct sdhci_pci_slot *slot = sdhci_priv(host);
	int rst_n_gpio = slot->rst_n_gpio;

	if (!gpio_is_valid(rst_n_gpio))
		return;
	gpio_set_value_cansleep(rst_n_gpio, 0);
	/* For eMMC, minimum is 1us but give it 10us for good measure */
	udelay(10);
	gpio_set_value_cansleep(rst_n_gpio, 1);
	/* For eMMC, minimum is 200us but give it 300us for good measure */
	usleep_range(300, 1000);
}