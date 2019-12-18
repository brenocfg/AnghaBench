#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_12__ {int /*<<< orphan*/  pd; void* size; void* iova; } ;
struct TYPE_11__ {struct ib_pd* pd; } ;
struct mlx5_ib_mr {int access_flags; TYPE_6__* umem; TYPE_4__ mmkey; TYPE_3__ ibmr; scalar_t__ allocated_from_cache; int /*<<< orphan*/  npages; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {struct ib_pd* pd; int /*<<< orphan*/  device; } ;
struct TYPE_14__ {void* length; void* address; } ;
struct TYPE_13__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_9__ {int /*<<< orphan*/  reg_pages; } ;
struct TYPE_10__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int IB_MR_REREG_TRANS ; 
 scalar_t__ IS_ERR (struct mlx5_ib_mr*) ; 
 int MLX5_IB_UPD_XLT_ACCESS ; 
 int MLX5_IB_UPD_XLT_ADDR ; 
 int MLX5_IB_UPD_XLT_PD ; 
 int PTR_ERR (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_mr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int destroy_mkey (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  ib_umem_release (TYPE_6__*) ; 
 scalar_t__ is_odp_mr (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_ib_can_use_umr (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,void*,void*,void*,int) ; 
 int mlx5_ib_update_xlt (struct mlx5_ib_mr*,int /*<<< orphan*/ ,int,int,int) ; 
 int mr_umem_get (struct mlx5_ib_dev*,struct ib_udata*,void*,void*,int,TYPE_6__**,int*,int*,int*,int*) ; 
 struct mlx5_ib_mr* reg_create (struct ib_mr*,struct ib_pd*,void*,void*,TYPE_6__*,int,int,int,int) ; 
 int rereg_umr (struct ib_pd*,struct mlx5_ib_mr*,int,int) ; 
 int /*<<< orphan*/  set_mr_fields (struct mlx5_ib_dev*,struct mlx5_ib_mr*,int,void*,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mr* to_mmr (struct ib_mr*) ; 
 TYPE_5__* to_mpd (struct ib_pd*) ; 
 int unreg_umr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  use_umr_mtt_update (struct mlx5_ib_mr*,void*,void*) ; 

int mlx5_ib_rereg_user_mr(struct ib_mr *ib_mr, int flags, u64 start,
			  u64 length, u64 virt_addr, int new_access_flags,
			  struct ib_pd *new_pd, struct ib_udata *udata)
{
	struct mlx5_ib_dev *dev = to_mdev(ib_mr->device);
	struct mlx5_ib_mr *mr = to_mmr(ib_mr);
	struct ib_pd *pd = (flags & IB_MR_REREG_PD) ? new_pd : ib_mr->pd;
	int access_flags = flags & IB_MR_REREG_ACCESS ?
			    new_access_flags :
			    mr->access_flags;
	int page_shift = 0;
	int upd_flags = 0;
	int npages = 0;
	int ncont = 0;
	int order = 0;
	u64 addr, len;
	int err;

	mlx5_ib_dbg(dev, "start 0x%llx, virt_addr 0x%llx, length 0x%llx, access_flags 0x%x\n",
		    start, virt_addr, length, access_flags);

	atomic_sub(mr->npages, &dev->mdev->priv.reg_pages);

	if (!mr->umem)
		return -EINVAL;

	if (is_odp_mr(mr))
		return -EOPNOTSUPP;

	if (flags & IB_MR_REREG_TRANS) {
		addr = virt_addr;
		len = length;
	} else {
		addr = mr->umem->address;
		len = mr->umem->length;
	}

	if (flags != IB_MR_REREG_PD) {
		/*
		 * Replace umem. This needs to be done whether or not UMR is
		 * used.
		 */
		flags |= IB_MR_REREG_TRANS;
		ib_umem_release(mr->umem);
		mr->umem = NULL;
		err = mr_umem_get(dev, udata, addr, len, access_flags,
				  &mr->umem, &npages, &page_shift, &ncont,
				  &order);
		if (err)
			goto err;
	}

	if (!mlx5_ib_can_use_umr(dev, true) ||
	    (flags & IB_MR_REREG_TRANS && !use_umr_mtt_update(mr, addr, len))) {
		/*
		 * UMR can't be used - MKey needs to be replaced.
		 */
		if (mr->allocated_from_cache)
			err = unreg_umr(dev, mr);
		else
			err = destroy_mkey(dev, mr);
		if (err)
			goto err;

		mr = reg_create(ib_mr, pd, addr, len, mr->umem, ncont,
				page_shift, access_flags, true);

		if (IS_ERR(mr)) {
			err = PTR_ERR(mr);
			mr = to_mmr(ib_mr);
			goto err;
		}

		mr->allocated_from_cache = 0;
	} else {
		/*
		 * Send a UMR WQE
		 */
		mr->ibmr.pd = pd;
		mr->access_flags = access_flags;
		mr->mmkey.iova = addr;
		mr->mmkey.size = len;
		mr->mmkey.pd = to_mpd(pd)->pdn;

		if (flags & IB_MR_REREG_TRANS) {
			upd_flags = MLX5_IB_UPD_XLT_ADDR;
			if (flags & IB_MR_REREG_PD)
				upd_flags |= MLX5_IB_UPD_XLT_PD;
			if (flags & IB_MR_REREG_ACCESS)
				upd_flags |= MLX5_IB_UPD_XLT_ACCESS;
			err = mlx5_ib_update_xlt(mr, 0, npages, page_shift,
						 upd_flags);
		} else {
			err = rereg_umr(pd, mr, access_flags, flags);
		}

		if (err)
			goto err;
	}

	set_mr_fields(dev, mr, npages, len, access_flags);

	return 0;

err:
	ib_umem_release(mr->umem);
	mr->umem = NULL;

	clean_mr(dev, mr);
	return err;
}