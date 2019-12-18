#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * nic_dmn; } ;
struct mlx5dr_table {TYPE_2__* dmn; TYPE_3__ tx; TYPE_3__ rx; int /*<<< orphan*/  table_type; int /*<<< orphan*/  matcher_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct TYPE_5__ {int type; int /*<<< orphan*/  mutex; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  MLX5DR_DOMAIN_TYPE_FDB 130 
#define  MLX5DR_DOMAIN_TYPE_NIC_RX 129 
#define  MLX5DR_DOMAIN_TYPE_NIC_TX 128 
 int /*<<< orphan*/  MLX5_FLOW_TABLE_TYPE_FDB ; 
 int /*<<< orphan*/  MLX5_FLOW_TABLE_TYPE_NIC_RX ; 
 int /*<<< orphan*/  MLX5_FLOW_TABLE_TYPE_NIC_TX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int dr_table_init_fdb (struct mlx5dr_table*) ; 
 int dr_table_init_nic (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_table_init(struct mlx5dr_table *tbl)
{
	int ret = 0;

	INIT_LIST_HEAD(&tbl->matcher_list);

	mutex_lock(&tbl->dmn->mutex);

	switch (tbl->dmn->type) {
	case MLX5DR_DOMAIN_TYPE_NIC_RX:
		tbl->table_type = MLX5_FLOW_TABLE_TYPE_NIC_RX;
		tbl->rx.nic_dmn = &tbl->dmn->info.rx;
		ret = dr_table_init_nic(tbl->dmn, &tbl->rx);
		break;
	case MLX5DR_DOMAIN_TYPE_NIC_TX:
		tbl->table_type = MLX5_FLOW_TABLE_TYPE_NIC_TX;
		tbl->tx.nic_dmn = &tbl->dmn->info.tx;
		ret = dr_table_init_nic(tbl->dmn, &tbl->tx);
		break;
	case MLX5DR_DOMAIN_TYPE_FDB:
		tbl->table_type = MLX5_FLOW_TABLE_TYPE_FDB;
		tbl->rx.nic_dmn = &tbl->dmn->info.rx;
		tbl->tx.nic_dmn = &tbl->dmn->info.tx;
		ret = dr_table_init_fdb(tbl);
		break;
	default:
		WARN_ON(true);
		break;
	}

	mutex_unlock(&tbl->dmn->mutex);

	return ret;
}