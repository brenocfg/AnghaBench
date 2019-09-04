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
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_2__ {int (* setup_tc ) (struct nfp_app*,struct net_device*,int,void*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct nfp_app*,struct net_device*,int,void*) ; 

__attribute__((used)) static inline int nfp_app_setup_tc(struct nfp_app *app,
				   struct net_device *netdev,
				   enum tc_setup_type type, void *type_data)
{
	if (!app || !app->type->setup_tc)
		return -EOPNOTSUPP;
	return app->type->setup_tc(app, netdev, type, type_data);
}