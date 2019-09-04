#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct jme_adapter {int /*<<< orphan*/  phy_lock; TYPE_1__ mii_if; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jme_restart_an(struct jme_adapter *jme)
{
	u32 bmcr;

	spin_lock_bh(&jme->phy_lock);
	bmcr = jme_mdio_read(jme->dev, jme->mii_if.phy_id, MII_BMCR);
	bmcr |= (BMCR_ANENABLE | BMCR_ANRESTART);
	jme_mdio_write(jme->dev, jme->mii_if.phy_id, MII_BMCR, bmcr);
	spin_unlock_bh(&jme->phy_lock);
}