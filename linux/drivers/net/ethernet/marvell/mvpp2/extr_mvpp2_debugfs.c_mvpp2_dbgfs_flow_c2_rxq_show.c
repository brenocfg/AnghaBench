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
typedef  int u8 ;
struct seq_file {struct mvpp2_dbgfs_c2_entry* private; } ;
struct mvpp2_dbgfs_c2_entry {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; } ;
struct mvpp2_cls_c2_entry {int* attr; } ;

/* Variables and functions */
 int MVPP22_CLS_C2_ATTR0_QHIGH_MASK ; 
 int MVPP22_CLS_C2_ATTR0_QHIGH_OFFS ; 
 int MVPP22_CLS_C2_ATTR0_QLOW_MASK ; 
 int MVPP22_CLS_C2_ATTR0_QLOW_OFFS ; 
 int /*<<< orphan*/  mvpp2_cls_c2_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mvpp2_cls_c2_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_c2_rxq_show(struct seq_file *s, void *unused)
{
	struct mvpp2_dbgfs_c2_entry *entry = s->private;
	struct mvpp2_cls_c2_entry c2;
	u8 qh, ql;

	mvpp2_cls_c2_read(entry->priv, entry->id, &c2);

	qh = (c2.attr[0] >> MVPP22_CLS_C2_ATTR0_QHIGH_OFFS) &
	     MVPP22_CLS_C2_ATTR0_QHIGH_MASK;

	ql = (c2.attr[0] >> MVPP22_CLS_C2_ATTR0_QLOW_OFFS) &
	     MVPP22_CLS_C2_ATTR0_QLOW_MASK;

	seq_printf(s, "%d\n", (qh << 3 | ql));

	return 0;
}