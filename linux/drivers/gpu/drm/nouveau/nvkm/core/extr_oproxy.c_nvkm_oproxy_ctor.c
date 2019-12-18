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
struct nvkm_oproxy_func {int dummy; } ;
struct nvkm_oproxy {struct nvkm_oproxy_func const* func; int /*<<< orphan*/  base; } ;
struct nvkm_oclass {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_object_ctor (int /*<<< orphan*/ *,struct nvkm_oclass const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_oproxy_func ; 

void
nvkm_oproxy_ctor(const struct nvkm_oproxy_func *func,
		 const struct nvkm_oclass *oclass, struct nvkm_oproxy *oproxy)
{
	nvkm_object_ctor(&nvkm_oproxy_func, oclass, &oproxy->base);
	oproxy->func = func;
}