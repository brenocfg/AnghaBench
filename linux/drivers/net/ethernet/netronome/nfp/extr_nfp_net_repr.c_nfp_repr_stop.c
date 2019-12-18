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
struct nfp_repr {int /*<<< orphan*/  app; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct nfp_repr* netdev_priv (struct net_device*) ; 
 int nfp_app_repr_stop (int /*<<< orphan*/ ,struct nfp_repr*) ; 
 int /*<<< orphan*/  nfp_port_configure (struct net_device*,int) ; 

__attribute__((used)) static int nfp_repr_stop(struct net_device *netdev)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	int err;

	err = nfp_app_repr_stop(repr->app, repr);
	if (err)
		return err;

	nfp_port_configure(netdev, false);
	return 0;
}