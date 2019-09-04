#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mlx4_en_priv {int rx_ring_num; TYPE_1__** rx_cq; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_2__* dev; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int MLX4_FLAG_MSI_X ; 
 scalar_t__ mlx4_is_slave (TYPE_2__*) ; 
 int mlx4_test_async (TYPE_2__*) ; 
 int mlx4_test_interrupt (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_test_interrupts(struct mlx4_en_priv *priv)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = 0;
	int i = 0;

	err = mlx4_test_async(mdev->dev);
	/* When not in MSI_X or slave, test only async */
	if (!(mdev->dev->flags & MLX4_FLAG_MSI_X) || mlx4_is_slave(mdev->dev))
		return err;

	/* A loop over all completion vectors of current port,
	 * for each vector check whether it works by mapping command
	 * completions to that vector and performing a NOP command
	 */
	for (i = 0; i < priv->rx_ring_num; i++) {
		err = mlx4_test_interrupt(mdev->dev, priv->rx_cq[i]->vector);
		if (err)
			break;
	}

	return err;
}