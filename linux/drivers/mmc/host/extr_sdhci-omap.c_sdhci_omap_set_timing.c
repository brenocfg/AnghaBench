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
typedef  size_t u8 ;
struct sdhci_omap_host {int flags; size_t timing; int /*<<< orphan*/  pinctrl; struct pinctrl_state** pinctrl_state; struct device* dev; } ;
struct pinctrl_state {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SDHCI_OMAP_REQUIRE_IODELAY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int pinctrl_select_state (int /*<<< orphan*/ ,struct pinctrl_state*) ; 
 int /*<<< orphan*/  sdhci_omap_start_clock (struct sdhci_omap_host*) ; 
 int /*<<< orphan*/  sdhci_omap_stop_clock (struct sdhci_omap_host*) ; 

__attribute__((used)) static void sdhci_omap_set_timing(struct sdhci_omap_host *omap_host, u8 timing)
{
	int ret;
	struct pinctrl_state *pinctrl_state;
	struct device *dev = omap_host->dev;

	if (!(omap_host->flags & SDHCI_OMAP_REQUIRE_IODELAY))
		return;

	if (omap_host->timing == timing)
		return;

	sdhci_omap_stop_clock(omap_host);

	pinctrl_state = omap_host->pinctrl_state[timing];
	ret = pinctrl_select_state(omap_host->pinctrl, pinctrl_state);
	if (ret) {
		dev_err(dev, "failed to select pinctrl state\n");
		return;
	}

	sdhci_omap_start_clock(omap_host);
	omap_host->timing = timing;
}