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
struct seq_file {struct mvpp2_dbgfs_flow_entry* private; } ;
struct mvpp2_dbgfs_flow_entry {int /*<<< orphan*/  flow; } ;
struct mvpp2_cls_flow {int /*<<< orphan*/  flow_id; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mvpp2_cls_flow* mvpp2_cls_flow_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_id_show(struct seq_file *s, void *unused)
{
	const struct mvpp2_dbgfs_flow_entry *entry = s->private;
	const struct mvpp2_cls_flow *f;

	f = mvpp2_cls_flow_get(entry->flow);
	if (!f)
		return -EINVAL;

	seq_printf(s, "%d\n", f->flow_id);

	return 0;
}