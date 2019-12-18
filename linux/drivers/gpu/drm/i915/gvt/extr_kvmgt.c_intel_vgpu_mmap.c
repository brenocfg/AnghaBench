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
typedef  scalar_t__ u64 ;
struct vm_area_struct {unsigned int vm_pgoff; scalar_t__ vm_end; scalar_t__ vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct mdev_device {int dummy; } ;
struct intel_vgpu {int /*<<< orphan*/  gvt; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned int VFIO_PCI_BAR2_REGION_INDEX ; 
 unsigned int VFIO_PCI_OFFSET_SHIFT ; 
 unsigned int VFIO_PCI_ROM_REGION_INDEX ; 
 int VM_SHARED ; 
 unsigned long gvt_aperture_pa_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_vgpu_in_aperture (struct intel_vgpu*,unsigned long) ; 
 struct intel_vgpu* mdev_get_drvdata (struct mdev_device*) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long vgpu_aperture_offset (struct intel_vgpu*) ; 
 unsigned long vgpu_aperture_sz (struct intel_vgpu*) ; 

__attribute__((used)) static int intel_vgpu_mmap(struct mdev_device *mdev, struct vm_area_struct *vma)
{
	unsigned int index;
	u64 virtaddr;
	unsigned long req_size, pgoff, req_start;
	pgprot_t pg_prot;
	struct intel_vgpu *vgpu = mdev_get_drvdata(mdev);

	index = vma->vm_pgoff >> (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT);
	if (index >= VFIO_PCI_ROM_REGION_INDEX)
		return -EINVAL;

	if (vma->vm_end < vma->vm_start)
		return -EINVAL;
	if ((vma->vm_flags & VM_SHARED) == 0)
		return -EINVAL;
	if (index != VFIO_PCI_BAR2_REGION_INDEX)
		return -EINVAL;

	pg_prot = vma->vm_page_prot;
	virtaddr = vma->vm_start;
	req_size = vma->vm_end - vma->vm_start;
	pgoff = vma->vm_pgoff &
		((1U << (VFIO_PCI_OFFSET_SHIFT - PAGE_SHIFT)) - 1);
	req_start = pgoff << PAGE_SHIFT;

	if (!intel_vgpu_in_aperture(vgpu, req_start))
		return -EINVAL;
	if (req_start + req_size >
	    vgpu_aperture_offset(vgpu) + vgpu_aperture_sz(vgpu))
		return -EINVAL;

	pgoff = (gvt_aperture_pa_base(vgpu->gvt) >> PAGE_SHIFT) + pgoff;

	return remap_pfn_range(vma, virtaddr, pgoff, req_size, pg_prot);
}