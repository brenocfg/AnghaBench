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
struct mlx4_en_priv {TYPE_1__* mdev; } ;
struct mlx4_en_cq {scalar_t__ type; int /*<<< orphan*/  mcq; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ TX_XDP ; 
 int /*<<< orphan*/  mlx4_cq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

void mlx4_en_deactivate_cq(struct mlx4_en_priv *priv, struct mlx4_en_cq *cq)
{
	if (cq->type != TX_XDP) {
		napi_disable(&cq->napi);
		netif_napi_del(&cq->napi);
	}

	mlx4_cq_free(priv->mdev->dev, &cq->mcq);
}