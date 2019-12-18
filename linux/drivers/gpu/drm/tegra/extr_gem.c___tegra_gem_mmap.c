#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_pgoff; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_flags; } ;
struct tegra_bo {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  pages; } ;
struct drm_gem_object {int /*<<< orphan*/  size; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MIXEDMAP ; 
 int /*<<< orphan*/  VM_PFNMAP ; 
 int dma_mmap_wc (int /*<<< orphan*/ ,struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vm_close (struct vm_area_struct*) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 struct tegra_bo* to_tegra_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 

int __tegra_gem_mmap(struct drm_gem_object *gem, struct vm_area_struct *vma)
{
	struct tegra_bo *bo = to_tegra_bo(gem);

	if (!bo->pages) {
		unsigned long vm_pgoff = vma->vm_pgoff;
		int err;

		/*
		 * Clear the VM_PFNMAP flag that was set by drm_gem_mmap(),
		 * and set the vm_pgoff (used as a fake buffer offset by DRM)
		 * to 0 as we want to map the whole buffer.
		 */
		vma->vm_flags &= ~VM_PFNMAP;
		vma->vm_pgoff = 0;

		err = dma_mmap_wc(gem->dev->dev, vma, bo->vaddr, bo->paddr,
				  gem->size);
		if (err < 0) {
			drm_gem_vm_close(vma);
			return err;
		}

		vma->vm_pgoff = vm_pgoff;
	} else {
		pgprot_t prot = vm_get_page_prot(vma->vm_flags);

		vma->vm_flags |= VM_MIXEDMAP;
		vma->vm_flags &= ~VM_PFNMAP;

		vma->vm_page_prot = pgprot_writecombine(prot);
	}

	return 0;
}