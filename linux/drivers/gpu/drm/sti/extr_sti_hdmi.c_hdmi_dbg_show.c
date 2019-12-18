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
struct sti_hdmi {int /*<<< orphan*/  regs; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGFS_DUMP (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGFS_DUMP_DI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBGFS_PRINT_INT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_XMAX ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_XMIN ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_YMAX ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_YMIN ; 
 int /*<<< orphan*/  HDMI_AUDIO_CFG ; 
 int /*<<< orphan*/  HDMI_AUDN ; 
 int /*<<< orphan*/  HDMI_CFG ; 
 int /*<<< orphan*/  HDMI_IFRAME_SLOT_AUDIO ; 
 int /*<<< orphan*/  HDMI_IFRAME_SLOT_AVI ; 
 int /*<<< orphan*/  HDMI_IFRAME_SLOT_VENDOR ; 
 int /*<<< orphan*/  HDMI_INT_EN ; 
 int /*<<< orphan*/  HDMI_SPDIF_FIFO_STATUS ; 
 int /*<<< orphan*/  HDMI_STA ; 
 int /*<<< orphan*/  HDMI_SW_DI_CFG ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_HEAD_WORD ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD0 ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD1 ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD2 ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD3 ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD4 ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD5 ; 
 int /*<<< orphan*/  HDMI_SW_DI_N_PKT_WORD6 ; 
 int /*<<< orphan*/  hdmi_dbg_cfg (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_dbg_sta (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_dbg_sw_di_cfg (struct seq_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_read (struct sti_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int hdmi_dbg_show(struct seq_file *s, void *data)
{
	struct drm_info_node *node = s->private;
	struct sti_hdmi *hdmi = (struct sti_hdmi *)node->info_ent->data;

	seq_printf(s, "HDMI: (vaddr = 0x%p)", hdmi->regs);
	DBGFS_DUMP("\n", HDMI_CFG);
	hdmi_dbg_cfg(s, hdmi_read(hdmi, HDMI_CFG));
	DBGFS_DUMP("", HDMI_INT_EN);
	DBGFS_DUMP("\n", HDMI_STA);
	hdmi_dbg_sta(s, hdmi_read(hdmi, HDMI_STA));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_XMIN);
	seq_putc(s, '\t');
	DBGFS_PRINT_INT("Xmin:", hdmi_read(hdmi, HDMI_ACTIVE_VID_XMIN));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_XMAX);
	seq_putc(s, '\t');
	DBGFS_PRINT_INT("Xmax:", hdmi_read(hdmi, HDMI_ACTIVE_VID_XMAX));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_YMIN);
	seq_putc(s, '\t');
	DBGFS_PRINT_INT("Ymin:", hdmi_read(hdmi, HDMI_ACTIVE_VID_YMIN));
	DBGFS_DUMP("", HDMI_ACTIVE_VID_YMAX);
	seq_putc(s, '\t');
	DBGFS_PRINT_INT("Ymax:", hdmi_read(hdmi, HDMI_ACTIVE_VID_YMAX));
	DBGFS_DUMP("", HDMI_SW_DI_CFG);
	hdmi_dbg_sw_di_cfg(s, hdmi_read(hdmi, HDMI_SW_DI_CFG));

	DBGFS_DUMP("\n", HDMI_AUDIO_CFG);
	DBGFS_DUMP("\n", HDMI_SPDIF_FIFO_STATUS);
	DBGFS_DUMP("\n", HDMI_AUDN);

	seq_printf(s, "\n AVI Infoframe (Data Island slot N=%d):",
		   HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WORD, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD0, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD1, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD2, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD3, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD4, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD5, HDMI_IFRAME_SLOT_AVI);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD6, HDMI_IFRAME_SLOT_AVI);
	seq_printf(s, "\n\n AUDIO Infoframe (Data Island slot N=%d):",
		   HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WORD, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD0, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD1, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD2, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD3, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD4, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD5, HDMI_IFRAME_SLOT_AUDIO);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD6, HDMI_IFRAME_SLOT_AUDIO);
	seq_printf(s, "\n\n VENDOR SPECIFIC Infoframe (Data Island slot N=%d):",
		   HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_HEAD_WORD, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD0, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD1, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD2, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD3, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD4, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD5, HDMI_IFRAME_SLOT_VENDOR);
	DBGFS_DUMP_DI(HDMI_SW_DI_N_PKT_WORD6, HDMI_IFRAME_SLOT_VENDOR);
	seq_putc(s, '\n');
	return 0;
}