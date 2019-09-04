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
typedef  size_t u32 ;
struct nvkm_vmm_pt {int /*<<< orphan*/ * pte; int /*<<< orphan*/ * pde; } ;
struct nvkm_vmm_desc {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LPT ; 
 int /*<<< orphan*/  NVKM_VMM_PDE_SPARSE ; 
 int /*<<< orphan*/  NVKM_VMM_PTE_SPARSE ; 
 scalar_t__ PGD ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
nvkm_vmm_sparse_ptes(const struct nvkm_vmm_desc *desc,
		     struct nvkm_vmm_pt *pgt, u32 ptei, u32 ptes)
{
	if (desc->type == PGD) {
		while (ptes--)
			pgt->pde[ptei++] = NVKM_VMM_PDE_SPARSE;
	} else
	if (desc->type == LPT) {
		memset(&pgt->pte[ptei], NVKM_VMM_PTE_SPARSE, ptes);
	}
}