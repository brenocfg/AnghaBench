#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_fid; } ;
struct bnxt {TYPE_1__ pf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FID_INVALID ; 
 scalar_t__ bnxt_dev_is_vf_rep (struct net_device*) ; 
 int /*<<< orphan*/  bnxt_vf_rep_get_fid (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_port_same_parent_id (int /*<<< orphan*/ ,struct net_device*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u16 bnxt_flow_get_dst_fid(struct bnxt *pf_bp, struct net_device *dev)
{
	struct bnxt *bp;

	/* check if dev belongs to the same switch */
	if (!netdev_port_same_parent_id(pf_bp->dev, dev)) {
		netdev_info(pf_bp->dev, "dev(ifindex=%d) not on same switch",
			    dev->ifindex);
		return BNXT_FID_INVALID;
	}

	/* Is dev a VF-rep? */
	if (bnxt_dev_is_vf_rep(dev))
		return bnxt_vf_rep_get_fid(dev);

	bp = netdev_priv(dev);
	return bp->pf.fw_fid;
}