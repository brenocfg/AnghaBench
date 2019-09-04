#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfp_repr {TYPE_2__* netdev; TYPE_1__* app; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfp_repr_free (struct nfp_repr*) ; 
 int /*<<< orphan*/  nfp_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_repr_clean (struct nfp_repr*) ; 

void nfp_repr_clean_and_free(struct nfp_repr *repr)
{
	nfp_info(repr->app->cpp, "Destroying Representor(%s)\n",
		 repr->netdev->name);
	nfp_repr_clean(repr);
	__nfp_repr_free(repr);
}