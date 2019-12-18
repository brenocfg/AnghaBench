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
typedef  scalar_t__ u64 ;
struct vm_area_struct {scalar_t__ vm_end; unsigned long vm_start; int vm_flags; } ;
struct ib_umem {int dummy; } ;
struct ib_udata {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int VM_WRITE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  ib_access_writable (int) ; 
 struct ib_umem* ib_umem_get (struct ib_udata*,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 unsigned long untagged_addr (scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ib_umem *mlx4_get_umem_mr(struct ib_udata *udata, u64 start,
					u64 length, int access_flags)
{
	/*
	 * Force registering the memory as writable if the underlying pages
	 * are writable.  This is so rereg can change the access permissions
	 * from readable to writable without having to run through ib_umem_get
	 * again
	 */
	if (!ib_access_writable(access_flags)) {
		unsigned long untagged_start = untagged_addr(start);
		struct vm_area_struct *vma;

		down_read(&current->mm->mmap_sem);
		/*
		 * FIXME: Ideally this would iterate over all the vmas that
		 * cover the memory, but for now it requires a single vma to
		 * entirely cover the MR to support RO mappings.
		 */
		vma = find_vma(current->mm, untagged_start);
		if (vma && vma->vm_end >= untagged_start + length &&
		    vma->vm_start <= untagged_start) {
			if (vma->vm_flags & VM_WRITE)
				access_flags |= IB_ACCESS_LOCAL_WRITE;
		} else {
			access_flags |= IB_ACCESS_LOCAL_WRITE;
		}

		up_read(&current->mm->mmap_sem);
	}

	return ib_umem_get(udata, start, length, access_flags, 0);
}