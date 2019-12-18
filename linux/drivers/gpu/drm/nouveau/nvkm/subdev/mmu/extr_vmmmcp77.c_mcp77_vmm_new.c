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
struct nvkm_vmm {int dummy; } ;
struct nvkm_mmu {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcp77_vmm ; 
 int nv04_vmm_new_ (int /*<<< orphan*/ *,struct nvkm_mmu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,struct lock_class_key*,char const*,struct nvkm_vmm**) ; 

int
mcp77_vmm_new(struct nvkm_mmu *mmu, bool managed, u64 addr, u64 size,
	      void *argv, u32 argc, struct lock_class_key *key,
	      const char *name, struct nvkm_vmm **pvmm)
{
	return nv04_vmm_new_(&mcp77_vmm, mmu, 0, managed, addr, size,
			     argv, argc, key, name, pvmm);
}