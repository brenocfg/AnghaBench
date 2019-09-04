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
struct seq_file {struct mvpp2_dbgfs_prs_entry* private; } ;
struct mvpp2_dbgfs_prs_entry {int tid; struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_prs_valid_show(struct seq_file *s, void *unused)
{
	struct mvpp2_dbgfs_prs_entry *entry = s->private;
	struct mvpp2 *priv = entry->priv;
	int tid = entry->tid;

	seq_printf(s, "%d\n", priv->prs_shadow[tid].valid ? 1 : 0);

	return 0;
}