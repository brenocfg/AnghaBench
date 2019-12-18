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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_ram {int dummy; } ;
struct nvkm_fb {int dummy; } ;
struct nv40_ram {struct nvkm_ram base; } ;
typedef  enum nvkm_ram_type { ____Placeholder_nvkm_ram_type } nvkm_ram_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nv40_ram* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv40_ram_func ; 
 int nvkm_ram_ctor (int /*<<< orphan*/ *,struct nvkm_fb*,int,int /*<<< orphan*/ ,struct nvkm_ram*) ; 

int
nv40_ram_new_(struct nvkm_fb *fb, enum nvkm_ram_type type, u64 size,
	      struct nvkm_ram **pram)
{
	struct nv40_ram *ram;
	if (!(ram = kzalloc(sizeof(*ram), GFP_KERNEL)))
		return -ENOMEM;
	*pram = &ram->base;
	return nvkm_ram_ctor(&nv40_ram_func, fb, type, size, &ram->base);
}