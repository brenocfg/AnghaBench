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
struct sti_vid {scalar_t__ regs; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGFS_DUMP (scalar_t__) ; 
 scalar_t__ VID_ALP ; 
 scalar_t__ VID_BC ; 
 scalar_t__ VID_CLF ; 
 scalar_t__ VID_CSAT ; 
 scalar_t__ VID_CTL ; 
 scalar_t__ VID_KEY1 ; 
 scalar_t__ VID_KEY2 ; 
 scalar_t__ VID_MPR0 ; 
 scalar_t__ VID_MPR1 ; 
 scalar_t__ VID_MPR2 ; 
 scalar_t__ VID_MPR3 ; 
 scalar_t__ VID_MST ; 
 scalar_t__ VID_TINT ; 
 scalar_t__ VID_VPO ; 
 scalar_t__ VID_VPS ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  vid_dbg_ctl (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vid_dbg_mst (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vid_dbg_vpo (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vid_dbg_vps (struct seq_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vid_dbg_show(struct seq_file *s, void *arg)
{
	struct drm_info_node *node = s->private;
	struct sti_vid *vid = (struct sti_vid *)node->info_ent->data;

	seq_printf(s, "VID: (vaddr= 0x%p)", vid->regs);

	DBGFS_DUMP(VID_CTL);
	vid_dbg_ctl(s, readl(vid->regs + VID_CTL));
	DBGFS_DUMP(VID_ALP);
	DBGFS_DUMP(VID_CLF);
	DBGFS_DUMP(VID_VPO);
	vid_dbg_vpo(s, readl(vid->regs + VID_VPO));
	DBGFS_DUMP(VID_VPS);
	vid_dbg_vps(s, readl(vid->regs + VID_VPS));
	DBGFS_DUMP(VID_KEY1);
	DBGFS_DUMP(VID_KEY2);
	DBGFS_DUMP(VID_MPR0);
	DBGFS_DUMP(VID_MPR1);
	DBGFS_DUMP(VID_MPR2);
	DBGFS_DUMP(VID_MPR3);
	DBGFS_DUMP(VID_MST);
	vid_dbg_mst(s, readl(vid->regs + VID_MST));
	DBGFS_DUMP(VID_BC);
	DBGFS_DUMP(VID_TINT);
	DBGFS_DUMP(VID_CSAT);
	seq_putc(s, '\n');
	return 0;
}