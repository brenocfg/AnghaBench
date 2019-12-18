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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_vmm_iter {int /*<<< orphan*/ * pt; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int nvkm_vmm_ref_ptes (struct nvkm_vmm_iter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_vmm_sparse_ptes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nvkm_vmm_sparse_ref_ptes(struct nvkm_vmm_iter *it, bool pfn, u32 ptei, u32 ptes)
{
	nvkm_vmm_sparse_ptes(it->desc, it->pt[0], ptei, ptes);
	return nvkm_vmm_ref_ptes(it, pfn, ptei, ptes);
}