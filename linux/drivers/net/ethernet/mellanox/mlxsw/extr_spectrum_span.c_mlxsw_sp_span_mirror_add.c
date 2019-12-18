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
struct net_device {int /*<<< orphan*/  name; } ;
struct mlxsw_sp_span_parms {int /*<<< orphan*/ * member_0; } ;
struct mlxsw_sp_span_entry_ops {int (* parms ) (struct net_device const*,struct mlxsw_sp_span_parms*) ;} ;
struct mlxsw_sp_span_entry {int id; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  dev; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 struct mlxsw_sp_span_entry* mlxsw_sp_span_entry_get (struct mlxsw_sp*,struct net_device const*,struct mlxsw_sp_span_entry_ops const*,struct mlxsw_sp_span_parms) ; 
 struct mlxsw_sp_span_entry_ops* mlxsw_sp_span_entry_ops (struct mlxsw_sp*,struct net_device const*) ; 
 int /*<<< orphan*/  mlxsw_sp_span_entry_put (struct mlxsw_sp*,struct mlxsw_sp_span_entry*) ; 
 int mlxsw_sp_span_inspected_port_add (struct mlxsw_sp_port*,struct mlxsw_sp_span_entry*,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device const*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device const*,struct mlxsw_sp_span_parms*) ; 

int mlxsw_sp_span_mirror_add(struct mlxsw_sp_port *from,
			     const struct net_device *to_dev,
			     enum mlxsw_sp_span_type type, bool bind,
			     int *p_span_id)
{
	struct mlxsw_sp *mlxsw_sp = from->mlxsw_sp;
	const struct mlxsw_sp_span_entry_ops *ops;
	struct mlxsw_sp_span_parms sparms = {NULL};
	struct mlxsw_sp_span_entry *span_entry;
	int err;

	ops = mlxsw_sp_span_entry_ops(mlxsw_sp, to_dev);
	if (!ops) {
		netdev_err(to_dev, "Cannot mirror to %s", to_dev->name);
		return -EOPNOTSUPP;
	}

	err = ops->parms(to_dev, &sparms);
	if (err)
		return err;

	span_entry = mlxsw_sp_span_entry_get(mlxsw_sp, to_dev, ops, sparms);
	if (!span_entry)
		return -ENOBUFS;

	netdev_dbg(from->dev, "Adding inspected port to SPAN entry %d\n",
		   span_entry->id);

	err = mlxsw_sp_span_inspected_port_add(from, span_entry, type, bind);
	if (err)
		goto err_port_bind;

	*p_span_id = span_entry->id;
	return 0;

err_port_bind:
	mlxsw_sp_span_entry_put(mlxsw_sp, span_entry);
	return err;
}