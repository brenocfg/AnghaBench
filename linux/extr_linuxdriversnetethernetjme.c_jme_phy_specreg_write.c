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
 int JM_PHY_SPEC_REG_WRITE ; 
 int /*<<< orphan*/  jme_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
jme_phy_specreg_write(struct jme_adapter *jme, u32 ext_reg, u32 phy_data)
{
	u32 phy_addr;

	phy_addr = JM_PHY_SPEC_REG_WRITE | ext_reg;
	jme_mdio_write(jme->dev, jme->mii_if.phy_id, JM_PHY_SPEC_DATA_REG,
			phy_data);
	jme_mdio_write(jme->dev, jme->mii_if.phy_id, JM_PHY_SPEC_ADDR_REG,
			phy_addr);
}