#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_special_mapping {int dummy; } ;
struct vm_fault {int pgoff; int /*<<< orphan*/  address; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; TYPE_2__* vm_mm; } ;
struct vdso_image {long sym_vvar_start; long sym_vvar_page; long sym_pvclock_page; long sym_hvclock_page; } ;
struct pvclock_vsyscall_time_info {int dummy; } ;
struct ms_hyperv_tsc_page {int dummy; } ;
struct TYPE_3__ {struct vdso_image* vdso_image; } ;
struct TYPE_4__ {TYPE_1__ context; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VCLOCK_HVCLOCK ; 
 int /*<<< orphan*/  VCLOCK_PVCLOCK ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_SIGBUS ; 
 int __pa (struct pvclock_vsyscall_time_info*) ; 
 int __pa_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __vvar_page ; 
 struct ms_hyperv_tsc_page* hv_get_tsc_page () ; 
 int /*<<< orphan*/  pgprot_decrypted (int /*<<< orphan*/ ) ; 
 struct pvclock_vsyscall_time_info* pvclock_get_pvti_cpu0_va () ; 
 scalar_t__ vclock_was_used (int /*<<< orphan*/ ) ; 
 int vm_insert_pfn (struct vm_area_struct*,int /*<<< orphan*/ ,int) ; 
 int vm_insert_pfn_prot (struct vm_area_struct*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int vmalloc_to_pfn (struct ms_hyperv_tsc_page*) ; 

__attribute__((used)) static int vvar_fault(const struct vm_special_mapping *sm,
		      struct vm_area_struct *vma, struct vm_fault *vmf)
{
	const struct vdso_image *image = vma->vm_mm->context.vdso_image;
	long sym_offset;
	int ret = -EFAULT;

	if (!image)
		return VM_FAULT_SIGBUS;

	sym_offset = (long)(vmf->pgoff << PAGE_SHIFT) +
		image->sym_vvar_start;

	/*
	 * Sanity check: a symbol offset of zero means that the page
	 * does not exist for this vdso image, not that the page is at
	 * offset zero relative to the text mapping.  This should be
	 * impossible here, because sym_offset should only be zero for
	 * the page past the end of the vvar mapping.
	 */
	if (sym_offset == 0)
		return VM_FAULT_SIGBUS;

	if (sym_offset == image->sym_vvar_page) {
		ret = vm_insert_pfn(vma, vmf->address,
				    __pa_symbol(&__vvar_page) >> PAGE_SHIFT);
	} else if (sym_offset == image->sym_pvclock_page) {
		struct pvclock_vsyscall_time_info *pvti =
			pvclock_get_pvti_cpu0_va();
		if (pvti && vclock_was_used(VCLOCK_PVCLOCK)) {
			ret = vm_insert_pfn_prot(
				vma,
				vmf->address,
				__pa(pvti) >> PAGE_SHIFT,
				pgprot_decrypted(vma->vm_page_prot));
		}
	} else if (sym_offset == image->sym_hvclock_page) {
		struct ms_hyperv_tsc_page *tsc_pg = hv_get_tsc_page();

		if (tsc_pg && vclock_was_used(VCLOCK_HVCLOCK))
			ret = vm_insert_pfn(vma, vmf->address,
					    vmalloc_to_pfn(tsc_pg));
	}

	if (ret == 0 || ret == -EBUSY)
		return VM_FAULT_NOPAGE;

	return VM_FAULT_SIGBUS;
}