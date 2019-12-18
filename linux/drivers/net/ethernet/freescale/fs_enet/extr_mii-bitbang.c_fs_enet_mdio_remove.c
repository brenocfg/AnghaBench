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
struct platform_device {int dummy; } ;
struct mii_bus {struct bb_info* priv; } ;
struct bb_info {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mdio_bitbang (struct mii_bus*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bb_info*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct mii_bus* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fs_enet_mdio_remove(struct platform_device *ofdev)
{
	struct mii_bus *bus = platform_get_drvdata(ofdev);
	struct bb_info *bitbang = bus->priv;

	mdiobus_unregister(bus);
	free_mdio_bitbang(bus);
	iounmap(bitbang->dir);
	kfree(bitbang);

	return 0;
}