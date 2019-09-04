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
struct nvkm_memory {int dummy; } ;
struct nvkm_falcon {TYPE_1__* func; int /*<<< orphan*/  user; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bind_context ) (struct nvkm_falcon*,struct nvkm_memory*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_falcon*,struct nvkm_memory*) ; 

void
nvkm_falcon_bind_context(struct nvkm_falcon *falcon, struct nvkm_memory *inst)
{
	if (!falcon->func->bind_context) {
		nvkm_error(falcon->user,
			   "Context binding not supported on this falcon!\n");
		return;
	}

	falcon->func->bind_context(falcon, inst);
}