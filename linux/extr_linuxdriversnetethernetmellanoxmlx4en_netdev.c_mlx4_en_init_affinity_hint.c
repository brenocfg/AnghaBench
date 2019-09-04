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
struct mlx4_en_rx_ring {int /*<<< orphan*/  affinity_mask; } ;
struct mlx4_en_priv {TYPE_2__* mdev; struct mlx4_en_rx_ring** rx_ring; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int numa_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpumask_local_spread (int,int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_init_affinity_hint(struct mlx4_en_priv *priv, int ring_idx)
{
	struct mlx4_en_rx_ring *ring = priv->rx_ring[ring_idx];
	int numa_node = priv->mdev->dev->numa_node;

	if (!zalloc_cpumask_var(&ring->affinity_mask, GFP_KERNEL))
		return -ENOMEM;

	cpumask_set_cpu(cpumask_local_spread(ring_idx, numa_node),
			ring->affinity_mask);
	return 0;
}