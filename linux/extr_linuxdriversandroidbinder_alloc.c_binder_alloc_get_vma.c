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
struct vm_area_struct {int dummy; } ;
struct binder_alloc {struct vm_area_struct* vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline struct vm_area_struct *binder_alloc_get_vma(
		struct binder_alloc *alloc)
{
	struct vm_area_struct *vma = NULL;

	if (alloc->vma) {
		/* Look at description in binder_alloc_set_vma */
		smp_rmb();
		vma = alloc->vma;
	}
	return vma;
}