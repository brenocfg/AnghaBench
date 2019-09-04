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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x_phy {int /*<<< orphan*/  type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ INT_PHY ; 
 int /*<<< orphan*/  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN ; 
 int bnx2x_populate_ext_phy (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct bnx2x_phy*) ; 
 int bnx2x_populate_int_phy (struct bnx2x*,int /*<<< orphan*/ ,scalar_t__,struct bnx2x_phy*) ; 

__attribute__((used)) static int bnx2x_populate_phy(struct bnx2x *bp, u8 phy_index, u32 shmem_base,
			      u32 shmem2_base, u8 port, struct bnx2x_phy *phy)
{
	phy->type = PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN;
	if (phy_index == INT_PHY)
		return bnx2x_populate_int_phy(bp, shmem_base, port, phy);

	return bnx2x_populate_ext_phy(bp, phy_index, shmem_base, shmem2_base,
					port, phy);
}