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
struct nvkm_instmem {int /*<<< orphan*/  subdev; } ;
struct nvkm_device {TYPE_1__* func; } ;
struct nv40_instmem {struct nvkm_instmem base; int /*<<< orphan*/  iomem; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resource_size ) (struct nvkm_device*,int) ;int /*<<< orphan*/  (* resource_addr ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ioremap_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nv40_instmem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv40_instmem ; 
 int /*<<< orphan*/  nvkm_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvkm_instmem_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_instmem*) ; 
 int /*<<< orphan*/  stub1 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  stub3 (struct nvkm_device*,int) ; 

int
nv40_instmem_new(struct nvkm_device *device, int index,
		 struct nvkm_instmem **pimem)
{
	struct nv40_instmem *imem;
	int bar;

	if (!(imem = kzalloc(sizeof(*imem), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_instmem_ctor(&nv40_instmem, device, index, &imem->base);
	*pimem = &imem->base;

	/* map bar */
	if (device->func->resource_size(device, 2))
		bar = 2;
	else
		bar = 3;

	imem->iomem = ioremap_wc(device->func->resource_addr(device, bar),
				 device->func->resource_size(device, bar));
	if (!imem->iomem) {
		nvkm_error(&imem->base.subdev, "unable to map PRAMIN BAR\n");
		return -EFAULT;
	}

	return 0;
}