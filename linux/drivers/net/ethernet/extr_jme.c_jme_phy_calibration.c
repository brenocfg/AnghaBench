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
 int JM_PHY_EXT_COMM_2_CALI_ENABLE ; 
 int JM_PHY_EXT_COMM_2_CALI_LATCH ; 
 int JM_PHY_EXT_COMM_2_CALI_MODE_0 ; 
 int /*<<< orphan*/  JM_PHY_EXT_COMM_2_REG ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int PHY_GAD_TEST_MODE_1 ; 
 int PHY_GAD_TEST_MODE_MSK ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jme_phy_off (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_phy_on (struct jme_adapter*) ; 
 int jme_phy_specreg_read (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_phy_specreg_write (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int
jme_phy_calibration(struct jme_adapter *jme)
{
	u32 ctrl1000, phy_data;

	jme_phy_off(jme);
	jme_phy_on(jme);
	/*  Enabel PHY test mode 1 */
	ctrl1000 = jme_mdio_read(jme->dev, jme->mii_if.phy_id, MII_CTRL1000);
	ctrl1000 &= ~PHY_GAD_TEST_MODE_MSK;
	ctrl1000 |= PHY_GAD_TEST_MODE_1;
	jme_mdio_write(jme->dev, jme->mii_if.phy_id, MII_CTRL1000, ctrl1000);

	phy_data = jme_phy_specreg_read(jme, JM_PHY_EXT_COMM_2_REG);
	phy_data &= ~JM_PHY_EXT_COMM_2_CALI_MODE_0;
	phy_data |= JM_PHY_EXT_COMM_2_CALI_LATCH |
			JM_PHY_EXT_COMM_2_CALI_ENABLE;
	jme_phy_specreg_write(jme, JM_PHY_EXT_COMM_2_REG, phy_data);
	msleep(20);
	phy_data = jme_phy_specreg_read(jme, JM_PHY_EXT_COMM_2_REG);
	phy_data &= ~(JM_PHY_EXT_COMM_2_CALI_ENABLE |
			JM_PHY_EXT_COMM_2_CALI_MODE_0 |
			JM_PHY_EXT_COMM_2_CALI_LATCH);
	jme_phy_specreg_write(jme, JM_PHY_EXT_COMM_2_REG, phy_data);

	/*  Disable PHY test mode */
	ctrl1000 = jme_mdio_read(jme->dev, jme->mii_if.phy_id, MII_CTRL1000);
	ctrl1000 &= ~PHY_GAD_TEST_MODE_MSK;
	jme_mdio_write(jme->dev, jme->mii_if.phy_id, MII_CTRL1000, ctrl1000);
	return 0;
}