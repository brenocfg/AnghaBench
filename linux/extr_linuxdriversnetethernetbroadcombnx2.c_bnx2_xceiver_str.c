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
struct bnx2 {scalar_t__ phy_port; int phy_flags; } ;

/* Variables and functions */
 int BNX2_PHY_FLAG_SERDES ; 
 scalar_t__ PORT_FIBRE ; 

__attribute__((used)) static char *
bnx2_xceiver_str(struct bnx2 *bp)
{
	return (bp->phy_port == PORT_FIBRE) ? "SerDes" :
		((bp->phy_flags & BNX2_PHY_FLAG_SERDES) ? "Remote Copper" :
		 "Copper");
}