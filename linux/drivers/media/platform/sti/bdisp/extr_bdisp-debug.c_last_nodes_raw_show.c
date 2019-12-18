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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {struct bdisp_dev* private; } ;
struct bdisp_node {scalar_t__ nip; } ;
struct TYPE_2__ {struct bdisp_node** copy_node; } ;
struct bdisp_dev {TYPE_1__ dbg; } ;

/* Variables and functions */
 int MAX_NB_NODE ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int last_nodes_raw_show(struct seq_file *s, void *data)
{
	struct bdisp_dev *bdisp = s->private;
	struct bdisp_node *node;
	u32 *val;
	int j, i = 0;

	if (!bdisp->dbg.copy_node[0]) {
		seq_puts(s, "No node built yet\n");
		return 0;
	}

	do {
		node = bdisp->dbg.copy_node[i];
		if (!node)
			break;

		seq_printf(s, "--------\nNode %d:\n", i);
		val = (u32 *)node;
		for (j = 0; j < sizeof(struct bdisp_node) / sizeof(u32); j++)
			seq_printf(s, "0x%08X\n", *val++);
	} while ((++i < MAX_NB_NODE) && node->nip);

	return 0;
}