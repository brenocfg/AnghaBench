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
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtt; } ;
struct mlx4_ib_cq {int /*<<< orphan*/  db; TYPE_2__ buf; int /*<<< orphan*/  umem; int /*<<< orphan*/  mcq; } ;
struct ib_cq {int /*<<< orphan*/  cqe; TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_cq*) ; 
 int /*<<< orphan*/  mlx4_cq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_db_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_db_unmap_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_free_cq_buf (struct mlx4_ib_dev*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_mtt_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx4_ib_cq* to_mcq (struct ib_cq*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 

int mlx4_ib_destroy_cq(struct ib_cq *cq)
{
	struct mlx4_ib_dev *dev = to_mdev(cq->device);
	struct mlx4_ib_cq *mcq = to_mcq(cq);

	mlx4_cq_free(dev->dev, &mcq->mcq);
	mlx4_mtt_cleanup(dev->dev, &mcq->buf.mtt);

	if (cq->uobject) {
		mlx4_ib_db_unmap_user(to_mucontext(cq->uobject->context), &mcq->db);
		ib_umem_release(mcq->umem);
	} else {
		mlx4_ib_free_cq_buf(dev, &mcq->buf, cq->cqe);
		mlx4_db_free(dev->dev, &mcq->db);
	}

	kfree(mcq);

	return 0;
}