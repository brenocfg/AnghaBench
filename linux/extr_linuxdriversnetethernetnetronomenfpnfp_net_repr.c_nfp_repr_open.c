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
 int nfp_app_repr_open (int /*<<< orphan*/ ,struct nfp_repr*) ; 
 int nfp_port_configure (struct net_device*,int) ; 

__attribute__((used)) static int nfp_repr_open(struct net_device *netdev)
{
	struct nfp_repr *repr = netdev_priv(netdev);
	int err;

	err = nfp_port_configure(netdev, true);
	if (err)
		return err;

	err = nfp_app_repr_open(repr->app, repr);
	if (err)
		goto err_port_disable;

	return 0;

err_port_disable:
	nfp_port_configure(netdev, false);
	return err;
}