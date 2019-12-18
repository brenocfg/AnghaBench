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
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {struct mvpp2_dbgfs_port_flow_entry* private; } ;
struct mvpp2_port {int /*<<< orphan*/  priv; int /*<<< orphan*/  id; } ;
struct mvpp2_dbgfs_port_flow_entry {struct mvpp2_port* port; TYPE_1__* dbg_fe; } ;
struct mvpp2_cls_flow_entry {int dummy; } ;
struct mvpp2_cls_flow {int /*<<< orphan*/  flow_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  flow; } ;

/* Variables and functions */
 int EINVAL ; 
 int MVPP2_CLS_FLT_HASH_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvpp2_cls_flow* mvpp2_cls_flow_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cls_flow_read (int /*<<< orphan*/ ,int,struct mvpp2_cls_flow_entry*) ; 
 int /*<<< orphan*/  mvpp2_flow_get_hek_fields (struct mvpp2_cls_flow_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_dbgfs_port_flow_hash_opt_show(struct seq_file *s, void *unused)
{
	struct mvpp2_dbgfs_port_flow_entry *entry = s->private;
	struct mvpp2_port *port = entry->port;
	struct mvpp2_cls_flow_entry fe;
	const struct mvpp2_cls_flow *f;
	int flow_index;
	u16 hash_opts;

	f = mvpp2_cls_flow_get(entry->dbg_fe->flow);
	if (!f)
		return -EINVAL;

	flow_index = MVPP2_CLS_FLT_HASH_ENTRY(entry->port->id, f->flow_id);

	mvpp2_cls_flow_read(port->priv, flow_index, &fe);

	hash_opts = mvpp2_flow_get_hek_fields(&fe);

	seq_printf(s, "0x%04x\n", hash_opts);

	return 0;
}