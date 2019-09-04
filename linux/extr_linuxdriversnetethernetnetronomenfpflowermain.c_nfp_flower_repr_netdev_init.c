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
struct nfp_app {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nfp_flower_setup_tc_egress_cb ; 
 int tc_setup_cb_egdev_register (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_flower_repr_netdev_init(struct nfp_app *app, struct net_device *netdev)
{
	return tc_setup_cb_egdev_register(netdev,
					  nfp_flower_setup_tc_egress_cb,
					  netdev_priv(netdev));
}