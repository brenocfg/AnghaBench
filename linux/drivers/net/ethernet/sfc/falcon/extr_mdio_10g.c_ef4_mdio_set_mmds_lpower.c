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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 unsigned int MDIO_DEVS_AN ; 
 int /*<<< orphan*/  ef4_mdio_set_mmd_lpower (struct ef4_nic*,int,int) ; 

void ef4_mdio_set_mmds_lpower(struct ef4_nic *efx,
			      int low_power, unsigned int mmd_mask)
{
	int mmd = 0;
	mmd_mask &= ~MDIO_DEVS_AN;
	while (mmd_mask) {
		if (mmd_mask & 1)
			ef4_mdio_set_mmd_lpower(efx, low_power, mmd);
		mmd_mask = (mmd_mask >> 1);
		mmd++;
	}
}