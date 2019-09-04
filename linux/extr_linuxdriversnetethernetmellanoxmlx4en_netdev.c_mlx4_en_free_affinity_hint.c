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
struct mlx4_en_priv {TYPE_1__** rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  affinity_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_en_free_affinity_hint(struct mlx4_en_priv *priv, int ring_idx)
{
	free_cpumask_var(priv->rx_ring[ring_idx]->affinity_mask);
}