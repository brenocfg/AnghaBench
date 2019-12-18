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
struct sti_mixer {scalar_t__ regs; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGFS_DUMP (scalar_t__) ; 
 scalar_t__ GAM_MIXER_ACT ; 
 scalar_t__ GAM_MIXER_AVO ; 
 scalar_t__ GAM_MIXER_AVS ; 
 scalar_t__ GAM_MIXER_BCO ; 
 scalar_t__ GAM_MIXER_BCS ; 
 scalar_t__ GAM_MIXER_BKC ; 
 scalar_t__ GAM_MIXER_CRB ; 
 scalar_t__ GAM_MIXER_CTL ; 
 scalar_t__ GAM_MIXER_MBP ; 
 scalar_t__ GAM_MIXER_MX0 ; 
 int /*<<< orphan*/  mixer_dbg_crb (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_dbg_ctl (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mixer_dbg_mxn (struct seq_file*,scalar_t__) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  sti_mixer_reg_read (struct sti_mixer*,scalar_t__) ; 
 int /*<<< orphan*/  sti_mixer_to_str (struct sti_mixer*) ; 

__attribute__((used)) static int mixer_dbg_show(struct seq_file *s, void *arg)
{
	struct drm_info_node *node = s->private;
	struct sti_mixer *mixer = (struct sti_mixer *)node->info_ent->data;

	seq_printf(s, "%s: (vaddr = 0x%p)",
		   sti_mixer_to_str(mixer), mixer->regs);

	DBGFS_DUMP(GAM_MIXER_CTL);
	mixer_dbg_ctl(s, sti_mixer_reg_read(mixer, GAM_MIXER_CTL));
	DBGFS_DUMP(GAM_MIXER_BKC);
	DBGFS_DUMP(GAM_MIXER_BCO);
	DBGFS_DUMP(GAM_MIXER_BCS);
	DBGFS_DUMP(GAM_MIXER_AVO);
	DBGFS_DUMP(GAM_MIXER_AVS);
	DBGFS_DUMP(GAM_MIXER_CRB);
	mixer_dbg_crb(s, sti_mixer_reg_read(mixer, GAM_MIXER_CRB));
	DBGFS_DUMP(GAM_MIXER_ACT);
	DBGFS_DUMP(GAM_MIXER_MBP);
	DBGFS_DUMP(GAM_MIXER_MX0);
	mixer_dbg_mxn(s, mixer->regs + GAM_MIXER_MX0);
	seq_putc(s, '\n');
	return 0;
}