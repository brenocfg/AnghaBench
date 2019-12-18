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
struct device {int dummy; } ;
struct brcmf_pub {int /*<<< orphan*/  wiphy; int /*<<< orphan*/  ops; } ;
struct brcmf_bus {struct brcmf_pub* drvr; } ;

/* Variables and functions */
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 

void brcmf_free(struct device *dev)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_pub *drvr = bus_if->drvr;

	if (!drvr)
		return;

	bus_if->drvr = NULL;

	kfree(drvr->ops);

	wiphy_free(drvr->wiphy);
}