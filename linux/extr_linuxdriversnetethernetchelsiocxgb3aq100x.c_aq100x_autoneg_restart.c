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
struct TYPE_2__ {int /*<<< orphan*/  prtad; } ;
struct cphy {TYPE_1__ mdio; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int aq100x_power_down (struct cphy*,int /*<<< orphan*/ ) ; 
 int mdio_set_flag (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int aq100x_autoneg_restart(struct cphy *phy)
{
	int err;

	err = aq100x_power_down(phy, 0);
	if (!err)
		err = mdio_set_flag(&phy->mdio, phy->mdio.prtad,
				    MDIO_MMD_AN, MDIO_CTRL1,
				    BMCR_ANENABLE | BMCR_ANRESTART, 1);

	return err;
}