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
typedef  int u32 ;
struct sdhci_omap_host {char* version; int /*<<< orphan*/  pinctrl; struct device* dev; } ;
struct pinctrl_state {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct pinctrl_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 struct pinctrl_state* pinctrl_lookup_state (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static struct pinctrl_state
*sdhci_omap_iodelay_pinctrl_state(struct sdhci_omap_host *omap_host, char *mode,
				  u32 *caps, u32 capmask)
{
	struct device *dev = omap_host->dev;
	char *version = omap_host->version;
	struct pinctrl_state *pinctrl_state = ERR_PTR(-ENODEV);
	char str[20];

	if (!(*caps & capmask))
		goto ret;

	if (version) {
		snprintf(str, 20, "%s-%s", mode, version);
		pinctrl_state = pinctrl_lookup_state(omap_host->pinctrl, str);
	}

	if (IS_ERR(pinctrl_state))
		pinctrl_state = pinctrl_lookup_state(omap_host->pinctrl, mode);

	if (IS_ERR(pinctrl_state)) {
		dev_err(dev, "no pinctrl state for %s mode", mode);
		*caps &= ~capmask;
	}

ret:
	return pinctrl_state;
}