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
struct mlx5_ib_mr {int /*<<< orphan*/  num_leaf_free; struct mlx5_ib_mr* parent; } ;
struct ib_umem {TYPE_1__* odp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; scalar_t__ dying; struct mlx5_ib_mr* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_end (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_odp_unmap_dma_pages (struct ib_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_start (struct ib_umem*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mr_leaf_free(struct ib_umem *umem, u64 start,
			u64 end, void *cookie)
{
	struct mlx5_ib_mr *mr = umem->odp_data->private, *imr = cookie;

	if (mr->parent != imr)
		return 0;

	ib_umem_odp_unmap_dma_pages(umem,
				    ib_umem_start(umem),
				    ib_umem_end(umem));

	if (umem->odp_data->dying)
		return 0;

	WRITE_ONCE(umem->odp_data->dying, 1);
	atomic_inc(&imr->num_leaf_free);
	schedule_work(&umem->odp_data->work);

	return 0;
}