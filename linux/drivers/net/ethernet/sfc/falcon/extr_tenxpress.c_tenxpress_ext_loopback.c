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
struct ef4_nic {scalar_t__ loopback_mode; } ;

/* Variables and functions */
 int LOOPBACK_NEAR_LBN ; 
 scalar_t__ LOOPBACK_PHYXS ; 
 int /*<<< orphan*/  MDIO_MMD_PHYXS ; 
 int /*<<< orphan*/  PHYXS_TEST1 ; 
 int /*<<< orphan*/  ef4_mdio_set_flag (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void tenxpress_ext_loopback(struct ef4_nic *efx)
{
	ef4_mdio_set_flag(efx, MDIO_MMD_PHYXS, PHYXS_TEST1,
			  1 << LOOPBACK_NEAR_LBN,
			  efx->loopback_mode == LOOPBACK_PHYXS);
}