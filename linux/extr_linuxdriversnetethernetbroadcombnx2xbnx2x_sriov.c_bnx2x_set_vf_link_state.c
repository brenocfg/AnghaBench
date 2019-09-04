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
struct bnx2x_virtf {int link_cfg; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 struct bnx2x_virtf* BP_VF (struct bnx2x*,int) ; 
 int EINVAL ; 
 int bnx2x_iov_link_update_vf (struct bnx2x*,int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

int bnx2x_set_vf_link_state(struct net_device *dev, int idx, int link_state)
{
	struct bnx2x *bp = netdev_priv(dev);
	struct bnx2x_virtf *vf = BP_VF(bp, idx);

	if (!vf)
		return -EINVAL;

	if (vf->link_cfg == link_state)
		return 0; /* nothing todo */

	vf->link_cfg = link_state;

	return bnx2x_iov_link_update_vf(bp, idx);
}