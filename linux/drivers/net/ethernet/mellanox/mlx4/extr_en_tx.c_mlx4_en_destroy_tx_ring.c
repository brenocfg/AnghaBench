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
struct mlx4_en_tx_ring {int /*<<< orphan*/ * tx_info; struct mlx4_en_tx_ring* bounce_buf; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  sp_wqres; int /*<<< orphan*/  qpn; int /*<<< orphan*/  sp_qp; int /*<<< orphan*/  bf; scalar_t__ bf_alloced; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_tx_ring*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_bf_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_qp_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_qp_release_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_qp_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx4_en_destroy_tx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_tx_ring **pring)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_tx_ring *ring = *pring;
	en_dbg(DRV, priv, "Destroying tx ring, qpn: %d\n", ring->qpn);

	if (ring->bf_alloced)
		mlx4_bf_free(mdev->dev, &ring->bf);
	mlx4_qp_remove(mdev->dev, &ring->sp_qp);
	mlx4_qp_free(mdev->dev, &ring->sp_qp);
	mlx4_qp_release_range(priv->mdev->dev, ring->qpn, 1);
	mlx4_free_hwq_res(mdev->dev, &ring->sp_wqres, ring->buf_size);
	kfree(ring->bounce_buf);
	ring->bounce_buf = NULL;
	kvfree(ring->tx_info);
	ring->tx_info = NULL;
	kfree(ring);
	*pring = NULL;
}