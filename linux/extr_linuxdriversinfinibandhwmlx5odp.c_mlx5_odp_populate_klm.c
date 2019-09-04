#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_klm {void* key; void* bcount; scalar_t__ va; } ;
struct TYPE_6__ {size_t lkey; struct ib_pd* pd; } ;
struct mlx5_ib_mr {TYPE_3__ ibmr; } ;
struct mlx5_ib_dev {size_t null_mkey; } ;
struct ib_umem_odp {struct mlx5_ib_mr* private; TYPE_2__* umem; } ;
struct ib_ucontext {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; TYPE_1__* uobject; } ;
struct TYPE_5__ {unsigned long address; } ;
struct TYPE_4__ {struct ib_ucontext* context; } ;

/* Variables and functions */
 int MLX5_IB_UPD_XLT_ZAP ; 
 size_t MLX5_IMR_MTT_SIZE ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 void* cpu_to_be32 (size_t) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int,unsigned long,int /*<<< orphan*/ ) ; 
 struct ib_umem_odp* odp_lookup (struct ib_ucontext*,size_t,size_t,struct mlx5_ib_mr*) ; 
 struct ib_umem_odp* odp_next (struct ib_umem_odp*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

void mlx5_odp_populate_klm(struct mlx5_klm *pklm, size_t offset,
			   size_t nentries, struct mlx5_ib_mr *mr, int flags)
{
	struct ib_pd *pd = mr->ibmr.pd;
	struct ib_ucontext *ctx = pd->uobject->context;
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct ib_umem_odp *odp;
	unsigned long va;
	int i;

	if (flags & MLX5_IB_UPD_XLT_ZAP) {
		for (i = 0; i < nentries; i++, pklm++) {
			pklm->bcount = cpu_to_be32(MLX5_IMR_MTT_SIZE);
			pklm->key = cpu_to_be32(dev->null_mkey);
			pklm->va = 0;
		}
		return;
	}

	odp = odp_lookup(ctx, offset * MLX5_IMR_MTT_SIZE,
			     nentries * MLX5_IMR_MTT_SIZE, mr);

	for (i = 0; i < nentries; i++, pklm++) {
		pklm->bcount = cpu_to_be32(MLX5_IMR_MTT_SIZE);
		va = (offset + i) * MLX5_IMR_MTT_SIZE;
		if (odp && odp->umem->address == va) {
			struct mlx5_ib_mr *mtt = odp->private;

			pklm->key = cpu_to_be32(mtt->ibmr.lkey);
			odp = odp_next(odp);
		} else {
			pklm->key = cpu_to_be32(dev->null_mkey);
		}
		mlx5_ib_dbg(dev, "[%d] va %lx key %x\n",
			    i, va, be32_to_cpu(pklm->key));
	}
}