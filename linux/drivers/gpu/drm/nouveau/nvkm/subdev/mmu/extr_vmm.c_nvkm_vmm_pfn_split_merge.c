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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {scalar_t__ addr; int mapped; scalar_t__ size; scalar_t__ memory; scalar_t__ part; } ;

/* Variables and functions */
 struct nvkm_vma* node (struct nvkm_vma*,struct nvkm_vma*) ; 
 struct nvkm_vma* nvkm_vmm_node_merge (struct nvkm_vmm*,struct nvkm_vma*,struct nvkm_vma*,struct nvkm_vma*,scalar_t__) ; 
 struct nvkm_vma* nvkm_vmm_node_split (struct nvkm_vmm*,struct nvkm_vma*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct nvkm_vma *
nvkm_vmm_pfn_split_merge(struct nvkm_vmm *vmm, struct nvkm_vma *vma,
			 u64 addr, u64 size, u8 page, bool map)
{
	struct nvkm_vma *prev = NULL;
	struct nvkm_vma *next = NULL;

	if (vma->addr == addr && vma->part && (prev = node(vma, prev))) {
		if (prev->memory || prev->mapped != map)
			prev = NULL;
	}

	if (vma->addr + vma->size == addr + size && (next = node(vma, next))) {
		if (!next->part ||
		    next->memory || next->mapped != map)
			next = NULL;
	}

	if (prev || next)
		return nvkm_vmm_node_merge(vmm, prev, vma, next, size);
	return nvkm_vmm_node_split(vmm, vma, addr, size);
}