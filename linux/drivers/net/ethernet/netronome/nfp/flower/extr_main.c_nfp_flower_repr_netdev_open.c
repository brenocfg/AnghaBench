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
struct nfp_repr {TYPE_1__* netdev; } ;
struct nfp_app {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_tx_wake_all_queues (TYPE_1__*) ; 
 int nfp_flower_cmsg_portmod (struct nfp_repr*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nfp_flower_repr_netdev_open(struct nfp_app *app, struct nfp_repr *repr)
{
	int err;

	err = nfp_flower_cmsg_portmod(repr, true, repr->netdev->mtu, false);
	if (err)
		return err;

	netif_tx_wake_all_queues(repr->netdev);

	return 0;
}