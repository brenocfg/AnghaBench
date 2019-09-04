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
struct nvkm_subdev {int dummy; } ;
struct nvkm_instmem {TYPE_1__* func; } ;
struct TYPE_2__ {int (* oneinit ) (struct nvkm_instmem*) ;} ;

/* Variables and functions */
 struct nvkm_instmem* nvkm_instmem (struct nvkm_subdev*) ; 
 int stub1 (struct nvkm_instmem*) ; 

__attribute__((used)) static int
nvkm_instmem_oneinit(struct nvkm_subdev *subdev)
{
	struct nvkm_instmem *imem = nvkm_instmem(subdev);
	if (imem->func->oneinit)
		return imem->func->oneinit(imem);
	return 0;
}