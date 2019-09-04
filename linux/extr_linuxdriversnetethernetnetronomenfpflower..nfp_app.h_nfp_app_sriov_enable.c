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
struct TYPE_2__ {int (* sriov_enable ) (struct nfp_app*,int) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct nfp_app*,int) ; 

__attribute__((used)) static inline int nfp_app_sriov_enable(struct nfp_app *app, int num_vfs)
{
	if (!app || !app->type->sriov_enable)
		return -EOPNOTSUPP;
	return app->type->sriov_enable(app, num_vfs);
}