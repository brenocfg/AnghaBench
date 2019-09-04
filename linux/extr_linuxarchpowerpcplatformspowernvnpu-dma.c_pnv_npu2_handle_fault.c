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
typedef  int u64 ;
struct page {int dummy; } ;
struct npu_context {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int /*<<< orphan*/  FOLL_WRITE ; 
 int /*<<< orphan*/  FW_FEATURE_OPAL ; 
 unsigned long NPU2_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int get_user_pages_remote (int /*<<< orphan*/ *,struct mm_struct*,uintptr_t,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 

int pnv_npu2_handle_fault(struct npu_context *context, uintptr_t *ea,
			unsigned long *flags, unsigned long *status, int count)
{
	u64 rc = 0, result = 0;
	int i, is_write;
	struct page *page[1];

	/* mmap_sem should be held so the struct_mm must be present */
	struct mm_struct *mm = context->mm;

	if (!firmware_has_feature(FW_FEATURE_OPAL))
		return -ENODEV;

	WARN_ON(!rwsem_is_locked(&mm->mmap_sem));

	for (i = 0; i < count; i++) {
		is_write = flags[i] & NPU2_WRITE;
		rc = get_user_pages_remote(NULL, mm, ea[i], 1,
					is_write ? FOLL_WRITE : 0,
					page, NULL, NULL);

		/*
		 * To support virtualised environments we will have to do an
		 * access to the page to ensure it gets faulted into the
		 * hypervisor. For the moment virtualisation is not supported in
		 * other areas so leave the access out.
		 */
		if (rc != 1) {
			status[i] = rc;
			result = -EFAULT;
			continue;
		}

		status[i] = 0;
		put_page(page[0]);
	}

	return result;
}