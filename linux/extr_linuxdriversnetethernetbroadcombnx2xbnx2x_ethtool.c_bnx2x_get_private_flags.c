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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct bnx2x {int flags; } ;

/* Variables and functions */
 int BNX2X_PRI_FLAG_FCOE ; 
 int BNX2X_PRI_FLAG_ISCSI ; 
 int BNX2X_PRI_FLAG_STORAGE ; 
 int /*<<< orphan*/  IS_MF_STORAGE_ONLY (struct bnx2x*) ; 
 int NO_FCOE_FLAG ; 
 int NO_ISCSI_FLAG ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 bnx2x_get_private_flags(struct net_device *dev)
{
	struct bnx2x *bp = netdev_priv(dev);
	u32 flags = 0;

	flags |= (!(bp->flags & NO_ISCSI_FLAG) ? 1 : 0) << BNX2X_PRI_FLAG_ISCSI;
	flags |= (!(bp->flags & NO_FCOE_FLAG)  ? 1 : 0) << BNX2X_PRI_FLAG_FCOE;
	flags |= (!!IS_MF_STORAGE_ONLY(bp)) << BNX2X_PRI_FLAG_STORAGE;

	return flags;
}