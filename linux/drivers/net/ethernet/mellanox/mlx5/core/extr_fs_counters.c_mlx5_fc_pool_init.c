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
struct mlx5_fc_pool {scalar_t__ threshold; scalar_t__ used_fcs; scalar_t__ available_fcs; int /*<<< orphan*/  unused; int /*<<< orphan*/  partially_used; int /*<<< orphan*/  fully_used; int /*<<< orphan*/  pool_lock; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_fc_pool_init(struct mlx5_fc_pool *fc_pool, struct mlx5_core_dev *dev)
{
	fc_pool->dev = dev;
	mutex_init(&fc_pool->pool_lock);
	INIT_LIST_HEAD(&fc_pool->fully_used);
	INIT_LIST_HEAD(&fc_pool->partially_used);
	INIT_LIST_HEAD(&fc_pool->unused);
	fc_pool->available_fcs = 0;
	fc_pool->used_fcs = 0;
	fc_pool->threshold = 0;
}