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
struct sti_cursor {scalar_t__ regs; int /*<<< orphan*/  plane; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CUR_AWE ; 
 scalar_t__ CUR_AWS ; 
 scalar_t__ CUR_CML ; 
 scalar_t__ CUR_CTL ; 
 scalar_t__ CUR_PML ; 
 scalar_t__ CUR_PMP ; 
 scalar_t__ CUR_SIZE ; 
 scalar_t__ CUR_VPO ; 
 int /*<<< orphan*/  DBGFS_DUMP (scalar_t__) ; 
 int /*<<< orphan*/  cursor_dbg_cml (struct seq_file*,struct sti_cursor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_dbg_pml (struct seq_file*,struct sti_cursor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_dbg_size (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_dbg_vpo (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  sti_plane_to_str (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cursor_dbg_show(struct seq_file *s, void *data)
{
	struct drm_info_node *node = s->private;
	struct sti_cursor *cursor = (struct sti_cursor *)node->info_ent->data;

	seq_printf(s, "%s: (vaddr = 0x%p)",
		   sti_plane_to_str(&cursor->plane), cursor->regs);

	DBGFS_DUMP(CUR_CTL);
	DBGFS_DUMP(CUR_VPO);
	cursor_dbg_vpo(s, readl(cursor->regs + CUR_VPO));
	DBGFS_DUMP(CUR_PML);
	cursor_dbg_pml(s, cursor, readl(cursor->regs + CUR_PML));
	DBGFS_DUMP(CUR_PMP);
	DBGFS_DUMP(CUR_SIZE);
	cursor_dbg_size(s, readl(cursor->regs + CUR_SIZE));
	DBGFS_DUMP(CUR_CML);
	cursor_dbg_cml(s, cursor, readl(cursor->regs + CUR_CML));
	DBGFS_DUMP(CUR_AWS);
	DBGFS_DUMP(CUR_AWE);
	seq_putc(s, '\n');
	return 0;
}