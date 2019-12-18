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
struct TYPE_2__ {int /*<<< orphan*/  (* vnic_free ) (struct nfp_app*,struct nfp_net*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfp_app*,struct nfp_net*) ; 

__attribute__((used)) static inline void nfp_app_vnic_free(struct nfp_app *app, struct nfp_net *nn)
{
	if (app->type->vnic_free)
		app->type->vnic_free(app, nn);
}