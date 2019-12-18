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
struct net_device {int dummy; } ;
struct ethtool_dump {int /*<<< orphan*/  len; int /*<<< orphan*/  flag; int /*<<< orphan*/  version; } ;
struct bnx2x {int /*<<< orphan*/  dump_preset_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DUMP_VERSION ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_get_preset_regs_len (struct net_device*,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_get_dump_flag(struct net_device *dev,
			       struct ethtool_dump *dump)
{
	struct bnx2x *bp = netdev_priv(dev);

	dump->version = BNX2X_DUMP_VERSION;
	dump->flag = bp->dump_preset_idx;
	/* Calculate the requested preset idx length */
	dump->len = bnx2x_get_preset_regs_len(dev, bp->dump_preset_idx);
	DP(BNX2X_MSG_ETHTOOL, "Get dump preset %d length=%d\n",
	   bp->dump_preset_idx, dump->len);
	return 0;
}