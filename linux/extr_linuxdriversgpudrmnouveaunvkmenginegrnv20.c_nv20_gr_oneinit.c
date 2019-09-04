#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvkm_gr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;
struct TYPE_6__ {TYPE_2__ engine; } ;
struct nv20_gr {int /*<<< orphan*/  ctxtab; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVKM_MEM_TARGET_INST ; 
 struct nv20_gr* nv20_gr (struct nvkm_gr*) ; 
 int nvkm_memory_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 

int
nv20_gr_oneinit(struct nvkm_gr *base)
{
	struct nv20_gr *gr = nv20_gr(base);
	return nvkm_memory_new(gr->base.engine.subdev.device,
			       NVKM_MEM_TARGET_INST, 32 * 4, 16,
			       true, &gr->ctxtab);
}