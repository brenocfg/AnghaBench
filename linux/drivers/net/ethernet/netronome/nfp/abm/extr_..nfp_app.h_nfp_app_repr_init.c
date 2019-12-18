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
struct TYPE_2__ {int (* repr_init ) (struct nfp_app*,struct net_device*) ;} ;

/* Variables and functions */
 int stub1 (struct nfp_app*,struct net_device*) ; 

__attribute__((used)) static inline int
nfp_app_repr_init(struct nfp_app *app, struct net_device *netdev)
{
	if (!app->type->repr_init)
		return 0;
	return app->type->repr_init(app, netdev);
}