#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bnx2x {TYPE_1__* fp; TYPE_3__* dev; TYPE_2__* sp_objs; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ETH_MAC ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int bnx2x_set_mac_one (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,unsigned long*) ; 
 int bnx2x_vfpf_config_mac (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bnx2x_set_eth_mac(struct bnx2x *bp, bool set)
{
	if (IS_PF(bp)) {
		unsigned long ramrod_flags = 0;

		DP(NETIF_MSG_IFUP, "Adding Eth MAC\n");
		__set_bit(RAMROD_COMP_WAIT, &ramrod_flags);
		return bnx2x_set_mac_one(bp, bp->dev->dev_addr,
					 &bp->sp_objs->mac_obj, set,
					 BNX2X_ETH_MAC, &ramrod_flags);
	} else { /* vf */
		return bnx2x_vfpf_config_mac(bp, bp->dev->dev_addr,
					     bp->fp->index, set);
	}
}