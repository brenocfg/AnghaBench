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
typedef  size_t u32 ;
struct vm_area_struct {scalar_t__ vm_end; scalar_t__ vm_start; int /*<<< orphan*/  vm_page_prot; int /*<<< orphan*/  vm_pgoff; } ;
struct mlx5_bfreg_info {int num_sys_pages; int num_static_sys_pages; size_t total_num_bfregs; size_t* sys_pages; int /*<<< orphan*/  lock; scalar_t__* count; int /*<<< orphan*/  lib_uar_4k; } ;
struct mlx5_ib_ucontext {int /*<<< orphan*/  ibucontext; struct mlx5_bfreg_info bfregi; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  enum mlx5_ib_mmap_cmd { ____Placeholder_mlx5_ib_mmap_cmd } mlx5_ib_mmap_cmd ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
#define  MLX5_IB_MMAP_ALLOC_WC 131 
#define  MLX5_IB_MMAP_NC_PAGE 130 
#define  MLX5_IB_MMAP_REGULAR_PAGE 129 
#define  MLX5_IB_MMAP_WC_PAGE 128 
 int MLX5_NON_FP_BFREGS_PER_UAR ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long get_extended_index (int /*<<< orphan*/ ) ; 
 unsigned long get_index (int /*<<< orphan*/ ) ; 
 int get_uars_per_sys_page (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_alloc_uar (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mlx5_cmd_free_uar (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_free_bfreg (struct mlx5_ib_dev*,struct mlx5_bfreg_info*,size_t) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,...) ; 
 int /*<<< orphan*/  mmap_cmd2str (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pat_enabled () ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int rdma_user_mmap_io (int /*<<< orphan*/ *,struct vm_area_struct*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uar_index2pfn (struct mlx5_ib_dev*,size_t) ; 

__attribute__((used)) static int uar_mmap(struct mlx5_ib_dev *dev, enum mlx5_ib_mmap_cmd cmd,
		    struct vm_area_struct *vma,
		    struct mlx5_ib_ucontext *context)
{
	struct mlx5_bfreg_info *bfregi = &context->bfregi;
	int err;
	unsigned long idx;
	phys_addr_t pfn;
	pgprot_t prot;
	u32 bfreg_dyn_idx = 0;
	u32 uar_index;
	int dyn_uar = (cmd == MLX5_IB_MMAP_ALLOC_WC);
	int max_valid_idx = dyn_uar ? bfregi->num_sys_pages :
				bfregi->num_static_sys_pages;

	if (vma->vm_end - vma->vm_start != PAGE_SIZE)
		return -EINVAL;

	if (dyn_uar)
		idx = get_extended_index(vma->vm_pgoff) + bfregi->num_static_sys_pages;
	else
		idx = get_index(vma->vm_pgoff);

	if (idx >= max_valid_idx) {
		mlx5_ib_warn(dev, "invalid uar index %lu, max=%d\n",
			     idx, max_valid_idx);
		return -EINVAL;
	}

	switch (cmd) {
	case MLX5_IB_MMAP_WC_PAGE:
	case MLX5_IB_MMAP_ALLOC_WC:
/* Some architectures don't support WC memory */
#if defined(CONFIG_X86)
		if (!pat_enabled())
			return -EPERM;
#elif !(defined(CONFIG_PPC) || (defined(CONFIG_ARM) && defined(CONFIG_MMU)))
			return -EPERM;
#endif
	/* fall through */
	case MLX5_IB_MMAP_REGULAR_PAGE:
		/* For MLX5_IB_MMAP_REGULAR_PAGE do the best effort to get WC */
		prot = pgprot_writecombine(vma->vm_page_prot);
		break;
	case MLX5_IB_MMAP_NC_PAGE:
		prot = pgprot_noncached(vma->vm_page_prot);
		break;
	default:
		return -EINVAL;
	}

	if (dyn_uar) {
		int uars_per_page;

		uars_per_page = get_uars_per_sys_page(dev, bfregi->lib_uar_4k);
		bfreg_dyn_idx = idx * (uars_per_page * MLX5_NON_FP_BFREGS_PER_UAR);
		if (bfreg_dyn_idx >= bfregi->total_num_bfregs) {
			mlx5_ib_warn(dev, "invalid bfreg_dyn_idx %u, max=%u\n",
				     bfreg_dyn_idx, bfregi->total_num_bfregs);
			return -EINVAL;
		}

		mutex_lock(&bfregi->lock);
		/* Fail if uar already allocated, first bfreg index of each
		 * page holds its count.
		 */
		if (bfregi->count[bfreg_dyn_idx]) {
			mlx5_ib_warn(dev, "wrong offset, idx %lu is busy, bfregn=%u\n", idx, bfreg_dyn_idx);
			mutex_unlock(&bfregi->lock);
			return -EINVAL;
		}

		bfregi->count[bfreg_dyn_idx]++;
		mutex_unlock(&bfregi->lock);

		err = mlx5_cmd_alloc_uar(dev->mdev, &uar_index);
		if (err) {
			mlx5_ib_warn(dev, "UAR alloc failed\n");
			goto free_bfreg;
		}
	} else {
		uar_index = bfregi->sys_pages[idx];
	}

	pfn = uar_index2pfn(dev, uar_index);
	mlx5_ib_dbg(dev, "uar idx 0x%lx, pfn %pa\n", idx, &pfn);

	err = rdma_user_mmap_io(&context->ibucontext, vma, pfn, PAGE_SIZE,
				prot);
	if (err) {
		mlx5_ib_err(dev,
			    "rdma_user_mmap_io failed with error=%d, mmap_cmd=%s\n",
			    err, mmap_cmd2str(cmd));
		goto err;
	}

	if (dyn_uar)
		bfregi->sys_pages[idx] = uar_index;
	return 0;

err:
	if (!dyn_uar)
		return err;

	mlx5_cmd_free_uar(dev->mdev, idx);

free_bfreg:
	mlx5_ib_free_bfreg(dev, bfregi, bfreg_dyn_idx);

	return err;
}