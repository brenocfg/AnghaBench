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
struct nvkm_ior {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOR_DBG (struct nvkm_ior*,char*) ; 
 int /*<<< orphan*/  kfree (struct nvkm_ior*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
nvkm_ior_del(struct nvkm_ior **pior)
{
	struct nvkm_ior *ior = *pior;
	if (ior) {
		IOR_DBG(ior, "dtor");
		list_del(&ior->head);
		kfree(*pior);
		*pior = NULL;
	}
}