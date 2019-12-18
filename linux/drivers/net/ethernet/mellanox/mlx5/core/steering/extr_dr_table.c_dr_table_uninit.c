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
struct mlx5dr_table {TYPE_1__* dmn; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
#define  MLX5DR_DOMAIN_TYPE_FDB 130 
#define  MLX5DR_DOMAIN_TYPE_NIC_RX 129 
#define  MLX5DR_DOMAIN_TYPE_NIC_TX 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dr_table_uninit_fdb (struct mlx5dr_table*) ; 
 int /*<<< orphan*/  dr_table_uninit_nic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_table_uninit(struct mlx5dr_table *tbl)
{
	mutex_lock(&tbl->dmn->mutex);

	switch (tbl->dmn->type) {
	case MLX5DR_DOMAIN_TYPE_NIC_RX:
		dr_table_uninit_nic(&tbl->rx);
		break;
	case MLX5DR_DOMAIN_TYPE_NIC_TX:
		dr_table_uninit_nic(&tbl->tx);
		break;
	case MLX5DR_DOMAIN_TYPE_FDB:
		dr_table_uninit_fdb(tbl);
		break;
	default:
		WARN_ON(true);
		break;
	}

	mutex_unlock(&tbl->dmn->mutex);
}