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
struct netdev_phys_item_id {int id_len; int /*<<< orphan*/  id; } ;
struct net_device {int dummy; } ;
struct bnxt {scalar_t__ eswitch_mode; int /*<<< orphan*/  switch_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 scalar_t__ DEVLINK_ESWITCH_MODE_SWITCHDEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

int bnxt_get_port_parent_id(struct net_device *dev,
			    struct netdev_phys_item_id *ppid)
{
	struct bnxt *bp = netdev_priv(dev);

	if (bp->eswitch_mode != DEVLINK_ESWITCH_MODE_SWITCHDEV)
		return -EOPNOTSUPP;

	/* The PF and it's VF-reps only support the switchdev framework */
	if (!BNXT_PF(bp))
		return -EOPNOTSUPP;

	ppid->id_len = sizeof(bp->switch_id);
	memcpy(ppid->id, bp->switch_id, ppid->id_len);

	return 0;
}