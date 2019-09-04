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
struct emac_instance {int /*<<< orphan*/  tah_dev; int /*<<< orphan*/  mdio_dev; int /*<<< orphan*/  rgmii_dev; int /*<<< orphan*/  zmii_dev; int /*<<< orphan*/  mal_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emac_put_deps(struct emac_instance *dev)
{
	of_dev_put(dev->mal_dev);
	of_dev_put(dev->zmii_dev);
	of_dev_put(dev->rgmii_dev);
	of_dev_put(dev->mdio_dev);
	of_dev_put(dev->tah_dev);
}