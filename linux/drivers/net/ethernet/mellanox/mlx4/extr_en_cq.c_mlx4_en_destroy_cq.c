#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx4_en_priv {struct mlx4_en_dev* mdev; int /*<<< orphan*/  port; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
struct mlx4_en_cq {scalar_t__ type; int /*<<< orphan*/ * buf; scalar_t__ buf_size; scalar_t__ vector; int /*<<< orphan*/  wqres; } ;

/* Variables and functions */
 scalar_t__ RX ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_cq*) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mlx4_is_eq_vector_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlx4_release_eq (int /*<<< orphan*/ ,scalar_t__) ; 

void mlx4_en_destroy_cq(struct mlx4_en_priv *priv, struct mlx4_en_cq **pcq)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_cq *cq = *pcq;

	mlx4_free_hwq_res(mdev->dev, &cq->wqres, cq->buf_size);
	if (mlx4_is_eq_vector_valid(mdev->dev, priv->port, cq->vector) &&
	    cq->type == RX)
		mlx4_release_eq(priv->mdev->dev, cq->vector);
	cq->vector = 0;
	cq->buf_size = 0;
	cq->buf = NULL;
	kfree(cq);
	*pcq = NULL;
}