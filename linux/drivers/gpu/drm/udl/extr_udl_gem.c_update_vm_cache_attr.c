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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct udl_gem_object {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int UDL_BO_CACHEABLE ; 
 int UDL_BO_WC ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_vm_cache_attr(struct udl_gem_object *obj,
				 struct vm_area_struct *vma)
{
	DRM_DEBUG_KMS("flags = 0x%x\n", obj->flags);

	/* non-cacheable as default. */
	if (obj->flags & UDL_BO_CACHEABLE) {
		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	} else if (obj->flags & UDL_BO_WC) {
		vma->vm_page_prot =
			pgprot_writecombine(vm_get_page_prot(vma->vm_flags));
	} else {
		vma->vm_page_prot =
			pgprot_noncached(vm_get_page_prot(vma->vm_flags));
	}
}