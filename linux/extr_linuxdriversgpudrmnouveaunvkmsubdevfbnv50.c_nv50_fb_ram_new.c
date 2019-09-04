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
struct nvkm_ram {int dummy; } ;
struct nvkm_fb {int dummy; } ;
struct nv50_fb {int /*<<< orphan*/  base; TYPE_1__* func; } ;
struct TYPE_2__ {int (* ram_new ) (int /*<<< orphan*/ *,struct nvkm_ram**) ;} ;

/* Variables and functions */
 struct nv50_fb* nv50_fb (struct nvkm_fb*) ; 
 int stub1 (int /*<<< orphan*/ *,struct nvkm_ram**) ; 

__attribute__((used)) static int
nv50_fb_ram_new(struct nvkm_fb *base, struct nvkm_ram **pram)
{
	struct nv50_fb *fb = nv50_fb(base);
	return fb->func->ram_new(&fb->base, pram);
}