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
struct mlx5dr_table {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; int /*<<< orphan*/  dmn; } ;

/* Variables and functions */
 int dr_table_init_nic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dr_table_uninit_nic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_table_init_fdb(struct mlx5dr_table *tbl)
{
	int ret;

	ret = dr_table_init_nic(tbl->dmn, &tbl->rx);
	if (ret)
		return ret;

	ret = dr_table_init_nic(tbl->dmn, &tbl->tx);
	if (ret)
		goto destroy_rx;

	return 0;

destroy_rx:
	dr_table_uninit_nic(&tbl->rx);
	return ret;
}