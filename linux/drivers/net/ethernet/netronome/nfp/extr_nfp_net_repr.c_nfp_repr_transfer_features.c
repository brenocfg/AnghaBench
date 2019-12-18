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
struct nfp_repr {TYPE_3__* dst; } ;
struct net_device {int /*<<< orphan*/  gso_max_segs; int /*<<< orphan*/  gso_max_size; } ;
struct TYPE_4__ {struct net_device* lower_dev; } ;
struct TYPE_5__ {TYPE_1__ port_info; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 

void
nfp_repr_transfer_features(struct net_device *netdev, struct net_device *lower)
{
	struct nfp_repr *repr = netdev_priv(netdev);

	if (repr->dst->u.port_info.lower_dev != lower)
		return;

	netdev->gso_max_size = lower->gso_max_size;
	netdev->gso_max_segs = lower->gso_max_segs;

	netdev_update_features(netdev);
}