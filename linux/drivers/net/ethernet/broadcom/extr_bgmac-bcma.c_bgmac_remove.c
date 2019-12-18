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
struct bgmac {int /*<<< orphan*/  mii_bus; } ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 struct bgmac* bcma_get_drvdata (struct bcma_device*) ; 
 int /*<<< orphan*/  bcma_mdio_mii_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set_drvdata (struct bcma_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bgmac_enet_remove (struct bgmac*) ; 
 int /*<<< orphan*/  kfree (struct bgmac*) ; 

__attribute__((used)) static void bgmac_remove(struct bcma_device *core)
{
	struct bgmac *bgmac = bcma_get_drvdata(core);

	bcma_mdio_mii_unregister(bgmac->mii_bus);
	bgmac_enet_remove(bgmac);
	bcma_set_drvdata(core, NULL);
	kfree(bgmac);
}