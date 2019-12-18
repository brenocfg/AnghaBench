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
struct ef4_nic {int phy_mode; int /*<<< orphan*/  wanted_fc; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* init_phy ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int HZ ; 
 int PHY_MODE_SPECIAL ; 
 int /*<<< orphan*/  TENXPRESS_REQUIRED_DEVS ; 
 int /*<<< orphan*/  ef4_link_set_wanted_fc (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_mdio_an_reconfigure (struct ef4_nic*) ; 
 int ef4_mdio_check_mmds (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int ef4_mdio_wait_reset_mmds (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 TYPE_2__* falcon_board (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_reset_xaui (struct ef4_nic*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int tenxpress_init (struct ef4_nic*) ; 

__attribute__((used)) static int tenxpress_phy_init(struct ef4_nic *efx)
{
	int rc;

	falcon_board(efx)->type->init_phy(efx);

	if (!(efx->phy_mode & PHY_MODE_SPECIAL)) {
		rc = ef4_mdio_wait_reset_mmds(efx, TENXPRESS_REQUIRED_DEVS);
		if (rc < 0)
			return rc;

		rc = ef4_mdio_check_mmds(efx, TENXPRESS_REQUIRED_DEVS);
		if (rc < 0)
			return rc;
	}

	rc = tenxpress_init(efx);
	if (rc < 0)
		return rc;

	/* Reinitialise flow control settings */
	ef4_link_set_wanted_fc(efx, efx->wanted_fc);
	ef4_mdio_an_reconfigure(efx);

	schedule_timeout_uninterruptible(HZ / 5); /* 200ms */

	/* Let XGXS and SerDes out of reset */
	falcon_reset_xaui(efx);

	return 0;
}