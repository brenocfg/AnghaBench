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
struct jme_adapter {TYPE_1__ mii_if; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  JM_PHY_SPEC_ADDR_REG ; 
 int /*<<< orphan*/  JM_PHY_SPEC_DATA_REG ; 
 int JM_PHY_SPEC_REG_READ ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jme_phy_specreg_read(struct jme_adapter *jme, u32 specreg)
{
	u32 phy_addr;

	phy_addr = JM_PHY_SPEC_REG_READ | specreg;
	jme_mdio_write(jme->dev, jme->mii_if.phy_id, JM_PHY_SPEC_ADDR_REG,
			phy_addr);
	return jme_mdio_read(jme->dev, jme->mii_if.phy_id,
			JM_PHY_SPEC_DATA_REG);
}