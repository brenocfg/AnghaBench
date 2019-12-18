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
struct mlx5_ib_mr {int npages; int /*<<< orphan*/  allocated_from_cache; int /*<<< orphan*/  num_pending_prefetch; int /*<<< orphan*/  live; struct ib_umem* umem; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; int /*<<< orphan*/  mr_srcu; } ;
struct ib_umem_odp {int /*<<< orphan*/  is_implicit_odp; } ;
struct ib_umem {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_pages; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_mr (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_end (struct ib_umem_odp*) ; 
 int /*<<< orphan*/  ib_umem_odp_release (struct ib_umem_odp*) ; 
 int /*<<< orphan*/  ib_umem_release (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_start (struct ib_umem_odp*) ; 
 scalar_t__ is_odp_mr (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_ib_free_implicit_mr (struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  mlx5_ib_invalidate_range (struct ib_umem_odp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_mr_cache_free (struct mlx5_ib_dev*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 struct ib_umem_odp* to_ib_umem_odp (struct ib_umem*) ; 

__attribute__((used)) static void dereg_mr(struct mlx5_ib_dev *dev, struct mlx5_ib_mr *mr)
{
	int npages = mr->npages;
	struct ib_umem *umem = mr->umem;

	if (is_odp_mr(mr)) {
		struct ib_umem_odp *umem_odp = to_ib_umem_odp(umem);

		/* Prevent new page faults and
		 * prefetch requests from succeeding
		 */
		WRITE_ONCE(mr->live, 0);

		/* Wait for all running page-fault handlers to finish. */
		synchronize_srcu(&dev->mr_srcu);

		/* dequeue pending prefetch requests for the mr */
		if (atomic_read(&mr->num_pending_prefetch))
			flush_workqueue(system_unbound_wq);
		WARN_ON(atomic_read(&mr->num_pending_prefetch));

		/* Destroy all page mappings */
		if (!umem_odp->is_implicit_odp)
			mlx5_ib_invalidate_range(umem_odp,
						 ib_umem_start(umem_odp),
						 ib_umem_end(umem_odp));
		else
			mlx5_ib_free_implicit_mr(mr);
		/*
		 * We kill the umem before the MR for ODP,
		 * so that there will not be any invalidations in
		 * flight, looking at the *mr struct.
		 */
		ib_umem_odp_release(umem_odp);
		atomic_sub(npages, &dev->mdev->priv.reg_pages);

		/* Avoid double-freeing the umem. */
		umem = NULL;
	}

	clean_mr(dev, mr);

	/*
	 * We should unregister the DMA address from the HCA before
	 * remove the DMA mapping.
	 */
	mlx5_mr_cache_free(dev, mr);
	ib_umem_release(umem);
	if (umem)
		atomic_sub(npages, &dev->mdev->priv.reg_pages);

	if (!mr->allocated_from_cache)
		kfree(mr);
}