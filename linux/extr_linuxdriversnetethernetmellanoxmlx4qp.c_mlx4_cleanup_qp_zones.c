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
struct mlx4_qp_table {int /*<<< orphan*/ * zones; int /*<<< orphan*/ * bitmap_gen; int /*<<< orphan*/ * zones_uids; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_bitmap {int dummy; } ;
struct TYPE_2__ {struct mlx4_qp_table qp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_bitmap_cleanup (struct mlx4_bitmap*) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_zone_allocator_destroy (int /*<<< orphan*/ *) ; 
 struct mlx4_bitmap* mlx4_zone_get_bitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_zone_remove_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_cleanup_qp_zones(struct mlx4_dev *dev)
{
	struct mlx4_qp_table *qp_table = &mlx4_priv(dev)->qp_table;

	if (qp_table->zones) {
		int i;

		for (i = 0;
		     i < sizeof(qp_table->zones_uids)/sizeof(qp_table->zones_uids[0]);
		     i++) {
			struct mlx4_bitmap *bitmap =
				mlx4_zone_get_bitmap(qp_table->zones,
						     qp_table->zones_uids[i]);

			mlx4_zone_remove_one(qp_table->zones, qp_table->zones_uids[i]);
			if (NULL == bitmap)
				continue;

			mlx4_bitmap_cleanup(bitmap);
		}
		mlx4_zone_allocator_destroy(qp_table->zones);
		kfree(qp_table->bitmap_gen);
		qp_table->bitmap_gen = NULL;
		qp_table->zones = NULL;
	}
}