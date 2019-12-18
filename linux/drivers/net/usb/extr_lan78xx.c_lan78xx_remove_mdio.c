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
struct lan78xx_net {int /*<<< orphan*/  mdiobus; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lan78xx_remove_mdio(struct lan78xx_net *dev)
{
	mdiobus_unregister(dev->mdiobus);
	mdiobus_free(dev->mdiobus);
}