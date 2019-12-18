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
struct nfp_app {TYPE_1__* type; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_uninit ) (struct nfp_app*,struct net_device*) ;} ;

/* Variables and functions */
 struct nfp_app* nfp_app_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct nfp_app*,struct net_device*) ; 

void nfp_app_ndo_uninit(struct net_device *netdev)
{
	struct nfp_app *app = nfp_app_from_netdev(netdev);

	if (app && app->type->ndo_uninit)
		app->type->ndo_uninit(app, netdev);
}