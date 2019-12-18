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
struct nfp_app {TYPE_1__* type; int /*<<< orphan*/  netdev_nb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct nfp_app*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfp_app*) ; 
 int /*<<< orphan*/  unregister_netdevice_notifier (int /*<<< orphan*/ *) ; 

void nfp_app_stop(struct nfp_app *app)
{
	unregister_netdevice_notifier(&app->netdev_nb);

	if (app->type->stop)
		app->type->stop(app);
}