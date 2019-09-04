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
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_pgoff; } ;
struct mlx5_ib_ucontext {int dummy; } ;
struct mlx5_ib_dev {TYPE_1__* mdev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  clock_info_page; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ MLX5_IB_CLOCK_INFO_V1 ; 
 scalar_t__ PAGE_SIZE ; 
 int VM_WRITE ; 
 scalar_t__ get_index (int /*<<< orphan*/ ) ; 
 int mlx5_ib_set_vma_data (struct vm_area_struct*,struct mlx5_ib_ucontext*) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 int remap_pfn_range (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_mmap_clock_info_page(struct mlx5_ib_dev *dev,
					struct vm_area_struct *vma,
					struct mlx5_ib_ucontext *context)
{
	phys_addr_t pfn;
	int err;

	if (vma->vm_end - vma->vm_start != PAGE_SIZE)
		return -EINVAL;

	if (get_index(vma->vm_pgoff) != MLX5_IB_CLOCK_INFO_V1)
		return -EOPNOTSUPP;

	if (vma->vm_flags & VM_WRITE)
		return -EPERM;

	if (!dev->mdev->clock_info_page)
		return -EOPNOTSUPP;

	pfn = page_to_pfn(dev->mdev->clock_info_page);
	err = remap_pfn_range(vma, vma->vm_start, pfn, PAGE_SIZE,
			      vma->vm_page_prot);
	if (err)
		return err;

	return mlx5_ib_set_vma_data(vma, context);
}