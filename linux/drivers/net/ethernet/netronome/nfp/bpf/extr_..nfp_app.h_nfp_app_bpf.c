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
struct nfp_net {int dummy; } ;
struct nfp_app {TYPE_1__* type; } ;
struct netdev_bpf {int dummy; } ;
struct TYPE_2__ {int (* bpf ) (struct nfp_app*,struct nfp_net*,struct netdev_bpf*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct nfp_app*,struct nfp_net*,struct netdev_bpf*) ; 

__attribute__((used)) static inline int nfp_app_bpf(struct nfp_app *app, struct nfp_net *nn,
			      struct netdev_bpf *bpf)
{
	if (!app || !app->type->bpf)
		return -EINVAL;
	return app->type->bpf(app, nn, bpf);
}