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
struct omap_hsmmc_host {int pbias_enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  pbias; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_set_pbias(struct omap_hsmmc_host *host, bool power_on)
{
	int ret;

	if (IS_ERR(host->pbias))
		return 0;

	if (power_on) {
		if (host->pbias_enabled == 0) {
			ret = regulator_enable(host->pbias);
			if (ret) {
				dev_err(host->dev, "pbias reg enable fail\n");
				return ret;
			}
			host->pbias_enabled = 1;
		}
	} else {
		if (host->pbias_enabled == 1) {
			ret = regulator_disable(host->pbias);
			if (ret) {
				dev_err(host->dev, "pbias reg disable fail\n");
				return ret;
			}
			host->pbias_enabled = 0;
		}
	}

	return 0;
}