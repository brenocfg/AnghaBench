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
struct mlxsw_sp_span_entry {int /*<<< orphan*/  id; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  mlxsw_sp; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 struct mlxsw_sp_span_entry* mlxsw_sp_span_entry_find_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_span_inspected_port_del (struct mlxsw_sp_port*,struct mlxsw_sp_span_entry*,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

void mlxsw_sp_span_mirror_del(struct mlxsw_sp_port *from, int span_id,
			      enum mlxsw_sp_span_type type, bool bind)
{
	struct mlxsw_sp_span_entry *span_entry;

	span_entry = mlxsw_sp_span_entry_find_by_id(from->mlxsw_sp, span_id);
	if (!span_entry) {
		netdev_err(from->dev, "no span entry found\n");
		return;
	}

	netdev_dbg(from->dev, "removing inspected port from SPAN entry %d\n",
		   span_entry->id);
	mlxsw_sp_span_inspected_port_del(from, span_entry, type, bind);
}