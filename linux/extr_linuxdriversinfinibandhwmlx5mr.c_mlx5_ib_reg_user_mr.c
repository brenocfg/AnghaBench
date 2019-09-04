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
typedef  int /*<<< orphan*/  u64 ;
struct ib_mr {int dummy; } ;
struct TYPE_2__ {int key; } ;
struct mlx5_ib_mr {struct ib_mr ibmr; struct ib_umem* umem; TYPE_1__ mmkey; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  slow_path_mutex; int /*<<< orphan*/  mdev; } ;
struct ib_umem {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INFINIBAND_USER_MEM ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct ib_mr* ERR_PTR (int) ; 
 int IB_ACCESS_ON_DEMAND ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_IB_UPD_XLT_ENABLE ; 
 int MLX5_IB_UPD_XLT_ZAP ; 
 int PTR_ERR (struct mlx5_ib_mr*) ; 
 struct mlx5_ib_mr* alloc_mr_from_cache (struct ib_pd*,struct ib_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  dereg_mr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int,...) ; 
 int mlx5_ib_update_xlt (struct mlx5_ib_mr*,int /*<<< orphan*/ ,int,int,int) ; 
 int mr_umem_get (struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ib_umem**,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct mlx5_ib_mr* reg_create (int /*<<< orphan*/ *,struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_umem*,int,int,int,int) ; 
 int /*<<< orphan*/  set_mr_fileds (struct mlx5_ib_dev*,struct mlx5_ib_mr*,int,int /*<<< orphan*/ ,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umr_can_modify_entity_size (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  umr_extended_translation_offset ; 
 scalar_t__ use_umr (struct mlx5_ib_dev*,int) ; 

struct ib_mr *mlx5_ib_reg_user_mr(struct ib_pd *pd, u64 start, u64 length,
				  u64 virt_addr, int access_flags,
				  struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct mlx5_ib_mr *mr = NULL;
	bool populate_mtts = false;
	struct ib_umem *umem;
	int page_shift;
	int npages;
	int ncont;
	int order;
	int err;

	if (!IS_ENABLED(CONFIG_INFINIBAND_USER_MEM))
		return ERR_PTR(-EOPNOTSUPP);

	mlx5_ib_dbg(dev, "start 0x%llx, virt_addr 0x%llx, length 0x%llx, access_flags 0x%x\n",
		    start, virt_addr, length, access_flags);

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	if (!start && length == U64_MAX) {
		if (!(access_flags & IB_ACCESS_ON_DEMAND) ||
		    !(dev->odp_caps.general_caps & IB_ODP_SUPPORT_IMPLICIT))
			return ERR_PTR(-EINVAL);

		mr = mlx5_ib_alloc_implicit_mr(to_mpd(pd), access_flags);
		if (IS_ERR(mr))
			return ERR_CAST(mr);
		return &mr->ibmr;
	}
#endif

	err = mr_umem_get(pd, start, length, access_flags, &umem, &npages,
			   &page_shift, &ncont, &order);

	if (err < 0)
		return ERR_PTR(err);

	if (use_umr(dev, order)) {
		mr = alloc_mr_from_cache(pd, umem, virt_addr, length, ncont,
					 page_shift, order, access_flags);
		if (PTR_ERR(mr) == -EAGAIN) {
			mlx5_ib_dbg(dev, "cache empty for order %d\n", order);
			mr = NULL;
		}
		populate_mtts = false;
	} else if (!MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset)) {
		if (access_flags & IB_ACCESS_ON_DEMAND) {
			err = -EINVAL;
			pr_err("Got MR registration for ODP MR > 512MB, not supported for Connect-IB\n");
			goto error;
		}
		populate_mtts = true;
	}

	if (!mr) {
		if (!umr_can_modify_entity_size(dev))
			populate_mtts = true;
		mutex_lock(&dev->slow_path_mutex);
		mr = reg_create(NULL, pd, virt_addr, length, umem, ncont,
				page_shift, access_flags, populate_mtts);
		mutex_unlock(&dev->slow_path_mutex);
	}

	if (IS_ERR(mr)) {
		err = PTR_ERR(mr);
		goto error;
	}

	mlx5_ib_dbg(dev, "mkey 0x%x\n", mr->mmkey.key);

	mr->umem = umem;
	set_mr_fileds(dev, mr, npages, length, access_flags);

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	update_odp_mr(mr);
#endif

	if (!populate_mtts) {
		int update_xlt_flags = MLX5_IB_UPD_XLT_ENABLE;

		if (access_flags & IB_ACCESS_ON_DEMAND)
			update_xlt_flags |= MLX5_IB_UPD_XLT_ZAP;

		err = mlx5_ib_update_xlt(mr, 0, ncont, page_shift,
					 update_xlt_flags);

		if (err) {
			dereg_mr(dev, mr);
			return ERR_PTR(err);
		}
	}

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	mr->live = 1;
#endif
	return &mr->ibmr;
error:
	ib_umem_release(umem);
	return ERR_PTR(err);
}