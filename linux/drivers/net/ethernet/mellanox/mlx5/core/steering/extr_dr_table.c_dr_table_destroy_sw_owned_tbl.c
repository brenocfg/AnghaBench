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
struct mlx5dr_table {int /*<<< orphan*/  table_type; int /*<<< orphan*/  table_id; TYPE_1__* dmn; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int mlx5dr_cmd_destroy_flow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dr_table_destroy_sw_owned_tbl(struct mlx5dr_table *tbl)
{
	return mlx5dr_cmd_destroy_flow_table(tbl->dmn->mdev,
					     tbl->table_id,
					     tbl->table_type);
}