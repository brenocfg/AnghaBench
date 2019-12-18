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
struct nic {scalar_t__ mdio_ctrl; } ;

/* Variables and functions */
 scalar_t__ mdio_ctrl_phy_mii_emulated ; 

__attribute__((used)) static inline int e100_phy_supports_mii(struct nic *nic)
{
	/* for now, just check it by comparing whether we
	   are using MII software emulation.
	*/
	return (nic->mdio_ctrl != mdio_ctrl_phy_mii_emulated);
}