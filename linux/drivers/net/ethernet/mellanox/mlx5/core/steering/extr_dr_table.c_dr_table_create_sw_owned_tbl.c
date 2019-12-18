#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_15__ {TYPE_5__* s_anchor; } ;
struct TYPE_12__ {TYPE_2__* s_anchor; } ;
struct mlx5dr_table {int /*<<< orphan*/  table_id; TYPE_9__* dmn; int /*<<< orphan*/  table_type; TYPE_6__ tx; TYPE_3__ rx; } ;
struct TYPE_16__ {scalar_t__ max_ft_level; } ;
struct TYPE_17__ {TYPE_7__ caps; } ;
struct TYPE_18__ {TYPE_8__ info; int /*<<< orphan*/  mdev; } ;
struct TYPE_14__ {TYPE_4__* chunk; } ;
struct TYPE_13__ {int /*<<< orphan*/  icm_addr; } ;
struct TYPE_11__ {TYPE_1__* chunk; } ;
struct TYPE_10__ {int /*<<< orphan*/  icm_addr; } ;

/* Variables and functions */
 int mlx5dr_cmd_create_flow_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_table_create_sw_owned_tbl(struct mlx5dr_table *tbl)
{
	u64 icm_addr_rx = 0;
	u64 icm_addr_tx = 0;
	int ret;

	if (tbl->rx.s_anchor)
		icm_addr_rx = tbl->rx.s_anchor->chunk->icm_addr;

	if (tbl->tx.s_anchor)
		icm_addr_tx = tbl->tx.s_anchor->chunk->icm_addr;

	ret = mlx5dr_cmd_create_flow_table(tbl->dmn->mdev,
					   tbl->table_type,
					   icm_addr_rx,
					   icm_addr_tx,
					   tbl->dmn->info.caps.max_ft_level - 1,
					   true, false, NULL,
					   &tbl->table_id);

	return ret;
}