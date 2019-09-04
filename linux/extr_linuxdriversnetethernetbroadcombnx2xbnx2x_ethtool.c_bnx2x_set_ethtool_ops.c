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
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_PF (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_ethtool_ops ; 
 int /*<<< orphan*/  bnx2x_vf_ethtool_ops ; 

void bnx2x_set_ethtool_ops(struct bnx2x *bp, struct net_device *netdev)
{
	netdev->ethtool_ops = (IS_PF(bp)) ?
		&bnx2x_ethtool_ops : &bnx2x_vf_ethtool_ops;
}