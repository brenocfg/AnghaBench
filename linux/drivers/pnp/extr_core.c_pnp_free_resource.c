#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pnp_resource {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pnp_resource*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void pnp_free_resource(struct pnp_resource *pnp_res)
{
	list_del(&pnp_res->list);
	kfree(pnp_res);
}