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
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct mlx4_mpt_entry {int dummy; } ;
struct TYPE_13__ {int access; int /*<<< orphan*/  mtt; void* size; void* iova; } ;
struct mlx4_ib_mr {TYPE_2__ mmr; TYPE_6__* umem; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;
struct TYPE_14__ {int /*<<< orphan*/  writable; } ;
struct TYPE_12__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int EPERM ; 
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int IB_MR_REREG_TRANS ; 
 scalar_t__ IS_ERR (TYPE_6__*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (TYPE_6__*) ; 
 int /*<<< orphan*/  convert_access (int) ; 
 scalar_t__ ib_access_writable (int) ; 
 int ib_umem_page_count (TYPE_6__*) ; 
 int /*<<< orphan*/  ib_umem_release (TYPE_6__*) ; 
 TYPE_6__* mlx4_get_umem_mr (struct ib_udata*,void*,void*,int) ; 
 int mlx4_ib_umem_write_mtt (struct mlx4_ib_dev*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int mlx4_mr_hw_change_access (int /*<<< orphan*/ ,struct mlx4_mpt_entry*,int /*<<< orphan*/ ) ; 
 int mlx4_mr_hw_change_pd (int /*<<< orphan*/ ,struct mlx4_mpt_entry*,int /*<<< orphan*/ ) ; 
 int mlx4_mr_hw_get_mpt (int /*<<< orphan*/ ,TYPE_2__*,struct mlx4_mpt_entry***) ; 
 int /*<<< orphan*/  mlx4_mr_hw_put_mpt (int /*<<< orphan*/ ,struct mlx4_mpt_entry**) ; 
 int mlx4_mr_hw_write_mpt (int /*<<< orphan*/ ,TYPE_2__*,struct mlx4_mpt_entry**) ; 
 int /*<<< orphan*/  mlx4_mr_rereg_mem_cleanup (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int mlx4_mr_rereg_mem_write (int /*<<< orphan*/ ,TYPE_2__*,void*,void*,int,int,struct mlx4_mpt_entry*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_mr* to_mmr (struct ib_mr*) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

int mlx4_ib_rereg_user_mr(struct ib_mr *mr, int flags,
			  u64 start, u64 length, u64 virt_addr,
			  int mr_access_flags, struct ib_pd *pd,
			  struct ib_udata *udata)
{
	struct mlx4_ib_dev *dev = to_mdev(mr->device);
	struct mlx4_ib_mr *mmr = to_mmr(mr);
	struct mlx4_mpt_entry *mpt_entry;
	struct mlx4_mpt_entry **pmpt_entry = &mpt_entry;
	int err;

	/* Since we synchronize this call and mlx4_ib_dereg_mr via uverbs,
	 * we assume that the calls can't run concurrently. Otherwise, a
	 * race exists.
	 */
	err =  mlx4_mr_hw_get_mpt(dev->dev, &mmr->mmr, &pmpt_entry);

	if (err)
		return err;

	if (flags & IB_MR_REREG_PD) {
		err = mlx4_mr_hw_change_pd(dev->dev, *pmpt_entry,
					   to_mpd(pd)->pdn);

		if (err)
			goto release_mpt_entry;
	}

	if (flags & IB_MR_REREG_ACCESS) {
		if (ib_access_writable(mr_access_flags) &&
		    !mmr->umem->writable) {
			err = -EPERM;
			goto release_mpt_entry;
		}

		err = mlx4_mr_hw_change_access(dev->dev, *pmpt_entry,
					       convert_access(mr_access_flags));

		if (err)
			goto release_mpt_entry;
	}

	if (flags & IB_MR_REREG_TRANS) {
		int shift;
		int n;

		mlx4_mr_rereg_mem_cleanup(dev->dev, &mmr->mmr);
		ib_umem_release(mmr->umem);
		mmr->umem = mlx4_get_umem_mr(udata, start, length,
					     mr_access_flags);
		if (IS_ERR(mmr->umem)) {
			err = PTR_ERR(mmr->umem);
			/* Prevent mlx4_ib_dereg_mr from free'ing invalid pointer */
			mmr->umem = NULL;
			goto release_mpt_entry;
		}
		n = ib_umem_page_count(mmr->umem);
		shift = PAGE_SHIFT;

		err = mlx4_mr_rereg_mem_write(dev->dev, &mmr->mmr,
					      virt_addr, length, n, shift,
					      *pmpt_entry);
		if (err) {
			ib_umem_release(mmr->umem);
			goto release_mpt_entry;
		}
		mmr->mmr.iova       = virt_addr;
		mmr->mmr.size       = length;

		err = mlx4_ib_umem_write_mtt(dev, &mmr->mmr.mtt, mmr->umem);
		if (err) {
			mlx4_mr_rereg_mem_cleanup(dev->dev, &mmr->mmr);
			ib_umem_release(mmr->umem);
			goto release_mpt_entry;
		}
	}

	/* If we couldn't transfer the MR to the HCA, just remember to
	 * return a failure. But dereg_mr will free the resources.
	 */
	err = mlx4_mr_hw_write_mpt(dev->dev, &mmr->mmr, pmpt_entry);
	if (!err && flags & IB_MR_REREG_ACCESS)
		mmr->mmr.access = mr_access_flags;

release_mpt_entry:
	mlx4_mr_hw_put_mpt(dev->dev, pmpt_entry);

	return err;
}