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
struct nvkm_vmm {int dummy; } ;
struct nvkm_vma {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_vma*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_vmm_free_remove (struct nvkm_vmm*,struct nvkm_vma*) ; 

__attribute__((used)) static inline void
nvkm_vmm_free_delete(struct nvkm_vmm *vmm, struct nvkm_vma *vma)
{
	nvkm_vmm_free_remove(vmm, vma);
	list_del(&vma->head);
	kfree(vma);
}