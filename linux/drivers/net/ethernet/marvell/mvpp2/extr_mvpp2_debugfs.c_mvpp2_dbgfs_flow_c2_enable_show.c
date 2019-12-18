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
struct seq_file {struct mvpp2_dbgfs_c2_entry* private; } ;
struct mvpp2_dbgfs_c2_entry {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; } ;
struct mvpp2_cls_c2_entry {int* attr; } ;

/* Variables and functions */
 int MVPP22_CLS_C2_ATTR2_RSS_EN ; 
 int /*<<< orphan*/  mvpp2_cls_c2_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mvpp2_cls_c2_entry*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_c2_enable_show(struct seq_file *s, void *unused)
{
	struct mvpp2_dbgfs_c2_entry *entry = s->private;
	struct mvpp2_cls_c2_entry c2;
	int enabled;

	mvpp2_cls_c2_read(entry->priv, entry->id, &c2);

	enabled = !!(c2.attr[2] & MVPP22_CLS_C2_ATTR2_RSS_EN);

	seq_printf(s, "%d\n", enabled);

	return 0;
}