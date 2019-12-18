#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
typedef  int u32 ;
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct devx_umem {int page_shift; int page_offset; TYPE_1__* umem; int /*<<< orphan*/  ncont; } ;
struct TYPE_6__ {int address; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  MLX5_IB_ATTR_DEVX_UMEM_REG_ACCESS ; 
 int /*<<< orphan*/  MLX5_IB_ATTR_DEVX_UMEM_REG_ADDR ; 
 int /*<<< orphan*/  MLX5_IB_ATTR_DEVX_UMEM_REG_LEN ; 
 int /*<<< orphan*/  MLX5_MKEY_PAGE_SHIFT_MASK ; 
 int PTR_ERR (TYPE_1__*) ; 
 int ib_check_mr_access (int) ; 
 TYPE_1__* ib_umem_get (int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_ib_cont_pages (TYPE_1__*,int,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uverbs_copy_from (size_t*,struct uverbs_attr_bundle*,int /*<<< orphan*/ ) ; 
 int uverbs_get_flags32 (int*,struct uverbs_attr_bundle*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int devx_umem_get(struct mlx5_ib_dev *dev, struct ib_ucontext *ucontext,
			 struct uverbs_attr_bundle *attrs,
			 struct devx_umem *obj)
{
	u64 addr;
	size_t size;
	u32 access;
	int npages;
	int err;
	u32 page_mask;

	if (uverbs_copy_from(&addr, attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_ADDR) ||
	    uverbs_copy_from(&size, attrs, MLX5_IB_ATTR_DEVX_UMEM_REG_LEN))
		return -EFAULT;

	err = uverbs_get_flags32(&access, attrs,
				 MLX5_IB_ATTR_DEVX_UMEM_REG_ACCESS,
				 IB_ACCESS_LOCAL_WRITE |
				 IB_ACCESS_REMOTE_WRITE |
				 IB_ACCESS_REMOTE_READ);
	if (err)
		return err;

	err = ib_check_mr_access(access);
	if (err)
		return err;

	obj->umem = ib_umem_get(&attrs->driver_udata, addr, size, access, 0);
	if (IS_ERR(obj->umem))
		return PTR_ERR(obj->umem);

	mlx5_ib_cont_pages(obj->umem, obj->umem->address,
			   MLX5_MKEY_PAGE_SHIFT_MASK, &npages,
			   &obj->page_shift, &obj->ncont, NULL);

	if (!npages) {
		ib_umem_release(obj->umem);
		return -EINVAL;
	}

	page_mask = (1 << obj->page_shift) - 1;
	obj->page_offset = obj->umem->address & page_mask;

	return 0;
}