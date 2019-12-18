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
struct mvpp2_port {size_t id; TYPE_1__* priv; TYPE_2__* dev; } ;
struct mvpp2_dbgfs_port_flow_entry {struct mvpp2_dbgfs_flow_entry* dbg_fe; struct mvpp2_port* port; } ;
struct mvpp2_dbgfs_flow_entry {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {struct mvpp2_dbgfs_port_flow_entry* port_flow_entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_3__* dbgfs_entries; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mvpp2_dbgfs_port_flow_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_dbgfs_port_flow_engine_fops ; 
 int /*<<< orphan*/  mvpp2_dbgfs_port_flow_hash_opt_fops ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_port_init(struct dentry *parent,
				      struct mvpp2_port *port,
				      struct mvpp2_dbgfs_flow_entry *entry)
{
	struct mvpp2_dbgfs_port_flow_entry *port_entry;
	struct dentry *port_dir;

	port_dir = debugfs_create_dir(port->dev->name, parent);

	port_entry = &port->priv->dbgfs_entries->port_flow_entries[port->id];

	port_entry->port = port;
	port_entry->dbg_fe = entry;

	debugfs_create_file("hash_opts", 0444, port_dir, port_entry,
			    &mvpp2_dbgfs_port_flow_hash_opt_fops);

	debugfs_create_file("engine", 0444, port_dir, port_entry,
			    &mvpp2_dbgfs_port_flow_engine_fops);

	return 0;
}