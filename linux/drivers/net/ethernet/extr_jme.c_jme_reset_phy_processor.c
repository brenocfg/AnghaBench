#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  phy_id; } ;
struct jme_adapter {TYPE_1__ mii_if; int /*<<< orphan*/  dev; TYPE_2__* pdev; } ;
struct TYPE_4__ {scalar_t__ device; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 scalar_t__ PCI_DEVICE_ID_JMICRON_JMC250 ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
jme_reset_phy_processor(struct jme_adapter *jme)
{
	u32 val;

	jme_mdio_write(jme->dev,
			jme->mii_if.phy_id,
			MII_ADVERTISE, ADVERTISE_ALL |
			ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM);

	if (jme->pdev->device == PCI_DEVICE_ID_JMICRON_JMC250)
		jme_mdio_write(jme->dev,
				jme->mii_if.phy_id,
				MII_CTRL1000,
				ADVERTISE_1000FULL | ADVERTISE_1000HALF);

	val = jme_mdio_read(jme->dev,
				jme->mii_if.phy_id,
				MII_BMCR);

	jme_mdio_write(jme->dev,
			jme->mii_if.phy_id,
			MII_BMCR, val | BMCR_RESET);
}