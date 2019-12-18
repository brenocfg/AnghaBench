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
struct nvkm_oproxy {int dummy; } ;
struct nvkm_oclass {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_oproxy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_oproxy_ctor (struct nvkm_oproxy_func const*,struct nvkm_oclass const*,struct nvkm_oproxy*) ; 

int
nvkm_oproxy_new_(const struct nvkm_oproxy_func *func,
		 const struct nvkm_oclass *oclass, struct nvkm_oproxy **poproxy)
{
	if (!(*poproxy = kzalloc(sizeof(**poproxy), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_oproxy_ctor(func, oclass, *poproxy);
	return 0;
}