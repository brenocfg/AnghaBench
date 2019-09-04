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
struct TYPE_2__ {int features; } ;
struct qede_reload_args {int /*<<< orphan*/  (* func ) (struct qede_dev*,struct qede_reload_args*) ;TYPE_1__ u; } ;
struct qede_dev {scalar_t__ xdp_prog; } ;
struct net_device {int features; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_GRO_HW ; 
 int /*<<< orphan*/  __qede_lock (struct qede_dev*) ; 
 int /*<<< orphan*/  __qede_unlock (struct qede_dev*) ; 
 struct qede_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qede_reload (struct qede_dev*,struct qede_reload_args*,int) ; 
 int /*<<< orphan*/  qede_set_features_reload (struct qede_dev*,struct qede_reload_args*) ; 
 int /*<<< orphan*/  stub1 (struct qede_dev*,struct qede_reload_args*) ; 

int qede_set_features(struct net_device *dev, netdev_features_t features)
{
	struct qede_dev *edev = netdev_priv(dev);
	netdev_features_t changes = features ^ dev->features;
	bool need_reload = false;

	if (changes & NETIF_F_GRO_HW)
		need_reload = true;

	if (need_reload) {
		struct qede_reload_args args;

		args.u.features = features;
		args.func = &qede_set_features_reload;

		/* Make sure that we definitely need to reload.
		 * In case of an eBPF attached program, there will be no FW
		 * aggregations, so no need to actually reload.
		 */
		__qede_lock(edev);
		if (edev->xdp_prog)
			args.func(edev, &args);
		else
			qede_reload(edev, &args, true);
		__qede_unlock(edev);

		return 1;
	}

	return 0;
}