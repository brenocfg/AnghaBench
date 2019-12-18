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
typedef  void* u64 ;
struct mlx5_mtt {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pd; void* size; void* iova; } ;
struct TYPE_4__ {struct ib_pd* pd; } ;
struct mlx5_ib_mr {int access_flags; int desc_size; TYPE_2__ mmkey; struct ib_umem* umem; TYPE_1__ ibmr; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_umem {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct mlx5_ib_mr* ERR_PTR (int) ; 
 int add_keys (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int) ; 
 struct mlx5_ib_mr* alloc_cached_mr (struct mlx5_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  order2idx (struct mlx5_ib_dev*,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static struct mlx5_ib_mr *alloc_mr_from_cache(
				  struct ib_pd *pd, struct ib_umem *umem,
				  u64 virt_addr, u64 len, int npages,
				  int page_shift, int order, int access_flags)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct mlx5_ib_mr *mr;
	int err = 0;
	int i;

	for (i = 0; i < 1; i++) {
		mr = alloc_cached_mr(dev, order);
		if (mr)
			break;

		err = add_keys(dev, order2idx(dev, order), 1);
		if (err && err != -EAGAIN) {
			mlx5_ib_warn(dev, "add_keys failed, err %d\n", err);
			break;
		}
	}

	if (!mr)
		return ERR_PTR(-EAGAIN);

	mr->ibmr.pd = pd;
	mr->umem = umem;
	mr->access_flags = access_flags;
	mr->desc_size = sizeof(struct mlx5_mtt);
	mr->mmkey.iova = virt_addr;
	mr->mmkey.size = len;
	mr->mmkey.pd = to_mpd(pd)->pdn;

	return mr;
}