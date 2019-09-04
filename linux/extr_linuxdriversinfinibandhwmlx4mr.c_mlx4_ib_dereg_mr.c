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
struct mlx4_ib_mr {scalar_t__ umem; int /*<<< orphan*/  mmr; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_mr*) ; 
 int /*<<< orphan*/  mlx4_free_priv_pages (struct mlx4_ib_mr*) ; 
 int mlx4_mr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_mr* to_mmr (struct ib_mr*) ; 

int mlx4_ib_dereg_mr(struct ib_mr *ibmr)
{
	struct mlx4_ib_mr *mr = to_mmr(ibmr);
	int ret;

	mlx4_free_priv_pages(mr);

	ret = mlx4_mr_free(to_mdev(ibmr->device)->dev, &mr->mmr);
	if (ret)
		return ret;
	if (mr->umem)
		ib_umem_release(mr->umem);
	kfree(mr);

	return 0;
}