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
typedef  int /*<<< orphan*/  u16 ;
struct scatterlist {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ixgbe_fcoe_ddp_setup (struct net_device*,int /*<<< orphan*/ ,struct scatterlist*,unsigned int,int /*<<< orphan*/ ) ; 

int ixgbe_fcoe_ddp_get(struct net_device *netdev, u16 xid,
		       struct scatterlist *sgl, unsigned int sgc)
{
	return ixgbe_fcoe_ddp_setup(netdev, xid, sgl, sgc, 0);
}