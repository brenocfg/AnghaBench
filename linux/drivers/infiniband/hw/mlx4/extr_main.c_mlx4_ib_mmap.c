#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int vm_pgoff; int /*<<< orphan*/  vm_page_prot; } ;
struct mlx4_ib_dev {TYPE_5__* dev; } ;
struct mlx4_clock_params {int offset; int /*<<< orphan*/  bar; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {int num_uars; int /*<<< orphan*/  bf_reg_size; } ;
struct TYPE_10__ {TYPE_3__* persist; TYPE_2__ caps; } ;
struct TYPE_6__ {int pfn; } ;
struct TYPE_9__ {TYPE_1__ uar; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int mlx4_get_internal_clock_params (TYPE_5__*,struct mlx4_clock_params*) ; 
 int pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int rdma_user_mmap_io (struct ib_ucontext*,struct vm_area_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_4__* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mlx4_ib_mmap(struct ib_ucontext *context, struct vm_area_struct *vma)
{
	struct mlx4_ib_dev *dev = to_mdev(context->device);

	switch (vma->vm_pgoff) {
	case 0:
		return rdma_user_mmap_io(context, vma,
					 to_mucontext(context)->uar.pfn,
					 PAGE_SIZE,
					 pgprot_noncached(vma->vm_page_prot));

	case 1:
		if (dev->dev->caps.bf_reg_size == 0)
			return -EINVAL;
		return rdma_user_mmap_io(
			context, vma,
			to_mucontext(context)->uar.pfn +
				dev->dev->caps.num_uars,
			PAGE_SIZE, pgprot_writecombine(vma->vm_page_prot));

	case 3: {
		struct mlx4_clock_params params;
		int ret;

		ret = mlx4_get_internal_clock_params(dev->dev, &params);
		if (ret)
			return ret;

		return rdma_user_mmap_io(
			context, vma,
			(pci_resource_start(dev->dev->persist->pdev,
					    params.bar) +
			 params.offset) >>
				PAGE_SHIFT,
			PAGE_SIZE, pgprot_noncached(vma->vm_page_prot));
	}

	default:
		return -EINVAL;
	}
}