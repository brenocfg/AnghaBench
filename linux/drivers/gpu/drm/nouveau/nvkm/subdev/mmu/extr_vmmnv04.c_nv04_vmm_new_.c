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
struct nv04_vmm_vn {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int nvif_unvers (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,struct nv04_vmm_vn) ; 
 int nvkm_vmm_new_ (struct nvkm_vmm_func const*,struct nvkm_mmu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lock_class_key*,char const*,struct nvkm_vmm**) ; 

int
nv04_vmm_new_(const struct nvkm_vmm_func *func, struct nvkm_mmu *mmu,
	      u32 pd_header, bool managed, u64 addr, u64 size,
	      void *argv, u32 argc, struct lock_class_key *key,
	      const char *name, struct nvkm_vmm **pvmm)
{
	union {
		struct nv04_vmm_vn vn;
	} *args = argv;
	int ret;

	ret = nvkm_vmm_new_(func, mmu, pd_header, managed, addr, size,
			    key, name, pvmm);
	if (ret)
		return ret;

	return nvif_unvers(-ENOSYS, &argv, &argc, args->vn);
}