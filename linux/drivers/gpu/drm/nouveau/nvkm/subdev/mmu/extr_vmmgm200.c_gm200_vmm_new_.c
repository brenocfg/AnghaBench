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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_func {int dummy; } ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu {int dummy; } ;
struct lock_class_key {int dummy; } ;
struct gm200_vmm_vn {int dummy; } ;
struct gm200_vmm_v0 {int bigpage; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int nvif_unpack (int,void**,int /*<<< orphan*/ *,struct gm200_vmm_v0,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int nvif_unvers (int,void**,int /*<<< orphan*/ *,struct gm200_vmm_vn) ; 
 int nvkm_vmm_new_ (struct nvkm_vmm_func const*,struct nvkm_mmu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_class_key*,char const*,struct nvkm_vmm**) ; 

int
gm200_vmm_new_(const struct nvkm_vmm_func *func_16,
	       const struct nvkm_vmm_func *func_17,
	       struct nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	       void *argv, u32 argc, struct lock_class_key *key,
	       const char *name, struct nvkm_vmm **pvmm)
{
	const struct nvkm_vmm_func *func;
	union {
		struct gm200_vmm_vn vn;
		struct gm200_vmm_v0 v0;
	} *args = argv;
	int ret = -ENOSYS;

	if (!(ret = nvif_unpack(ret, &argv, &argc, args->v0, 0, 0, false))) {
		switch (args->v0.bigpage) {
		case 16: func = func_16; break;
		case 17: func = func_17; break;
		default:
			return -EINVAL;
		}
	} else
	if (!(ret = nvif_unvers(ret, &argv, &argc, args->vn))) {
		func = func_17;
	} else
		return ret;

	return nvkm_vmm_new_(func, mmu, 0, managed, addr, size, key, name, pvmm);
}