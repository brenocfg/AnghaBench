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
struct nfp_repr {int dummy; } ;
struct nfp_app {TYPE_1__* type; } ;
struct TYPE_2__ {int (* repr_stop ) (struct nfp_app*,struct nfp_repr*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct nfp_app*,struct nfp_repr*) ; 

__attribute__((used)) static inline int nfp_app_repr_stop(struct nfp_app *app, struct nfp_repr *repr)
{
	if (!app->type->repr_stop)
		return -EINVAL;
	return app->type->repr_stop(app, repr);
}