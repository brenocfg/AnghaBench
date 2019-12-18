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
struct sfp {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; scalar_t__ mod_phy; int /*<<< orphan*/  sfp_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sfp_hwmon_remove (struct sfp*) ; 
 int /*<<< orphan*/  sfp_module_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfp_module_tx_disable (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_phy_detach (struct sfp*) ; 

__attribute__((used)) static void sfp_sm_mod_remove(struct sfp *sfp)
{
	sfp_module_remove(sfp->sfp_bus);

	sfp_hwmon_remove(sfp);

	if (sfp->mod_phy)
		sfp_sm_phy_detach(sfp);

	sfp_module_tx_disable(sfp);

	memset(&sfp->id, 0, sizeof(sfp->id));

	dev_info(sfp->dev, "module removed\n");
}