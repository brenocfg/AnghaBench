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
struct nvkm_dma_func {int dummy; } ;
struct nvkm_dma {int /*<<< orphan*/  engine; struct nvkm_dma_func const* func; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nvkm_dma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_dma ; 
 int nvkm_engine_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,int,int /*<<< orphan*/ *) ; 

int
nvkm_dma_new_(const struct nvkm_dma_func *func, struct nvkm_device *device,
	      int index, struct nvkm_dma **pdma)
{
	struct nvkm_dma *dma;

	if (!(dma = *pdma = kzalloc(sizeof(*dma), GFP_KERNEL)))
		return -ENOMEM;
	dma->func = func;

	return nvkm_engine_ctor(&nvkm_dma, device, index, true, &dma->engine);
}