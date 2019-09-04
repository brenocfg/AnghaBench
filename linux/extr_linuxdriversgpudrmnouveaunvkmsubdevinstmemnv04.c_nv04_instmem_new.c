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
struct nvkm_instmem {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct nv04_instmem {struct nvkm_instmem base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv04_instmem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_instmem ; 
 int /*<<< orphan*/  nvkm_instmem_ctor (int /*<<< orphan*/ *,struct nvkm_device*,int,struct nvkm_instmem*) ; 

int
nv04_instmem_new(struct nvkm_device *device, int index,
		 struct nvkm_instmem **pimem)
{
	struct nv04_instmem *imem;

	if (!(imem = kzalloc(sizeof(*imem), GFP_KERNEL)))
		return -ENOMEM;
	nvkm_instmem_ctor(&nv04_instmem, device, index, &imem->base);
	*pimem = &imem->base;
	return 0;
}