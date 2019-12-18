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
struct flow_action_entry {struct net_device* dev; } ;
struct bnxt_tc_actions {struct net_device* dst_dev; int /*<<< orphan*/  flags; } ;
struct bnxt {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_TC_ACTION_FLAG_FWD ; 
 int EINVAL ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bnxt_tc_parse_redir(struct bnxt *bp,
			       struct bnxt_tc_actions *actions,
			       const struct flow_action_entry *act)
{
	struct net_device *dev = act->dev;

	if (!dev) {
		netdev_info(bp->dev, "no dev in mirred action");
		return -EINVAL;
	}

	actions->flags |= BNXT_TC_ACTION_FLAG_FWD;
	actions->dst_dev = dev;
	return 0;
}