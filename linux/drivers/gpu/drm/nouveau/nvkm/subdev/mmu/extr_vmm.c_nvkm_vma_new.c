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
typedef  void* u64 ;
struct nvkm_vma {void* refd; void* page; void* size; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* NVKM_VMA_PAGE_NONE ; 
 struct nvkm_vma* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct nvkm_vma *
nvkm_vma_new(u64 addr, u64 size)
{
	struct nvkm_vma *vma = kzalloc(sizeof(*vma), GFP_KERNEL);
	if (vma) {
		vma->addr = addr;
		vma->size = size;
		vma->page = NVKM_VMA_PAGE_NONE;
		vma->refd = NVKM_VMA_PAGE_NONE;
	}
	return vma;
}