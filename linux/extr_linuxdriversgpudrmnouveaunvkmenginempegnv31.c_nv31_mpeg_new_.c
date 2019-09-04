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
struct nvkm_engine {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv31_mpeg_func {int dummy; } ;
struct nv31_mpeg {struct nvkm_engine engine; struct nv31_mpeg_func const* func; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv31_mpeg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv31_mpeg_ ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,struct nvkm_engine*) ; 

int
nv31_mpeg_new_(const struct nv31_mpeg_func *func, struct nvkm_device *device,
	       int index, struct nvkm_engine **pmpeg)
{
	struct nv31_mpeg *mpeg;

	if (!(mpeg = kzalloc(sizeof(*mpeg), GFP_KERNEL)))
		return -ENOMEM;
	mpeg->func = func;
	*pmpeg = &mpeg->engine;

	return nvkm_engine_ctor(&nv31_mpeg_, device, index,
				true, &mpeg->engine);
}