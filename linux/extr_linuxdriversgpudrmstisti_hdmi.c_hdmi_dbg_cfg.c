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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGFS_PRINT_STR (char*,char*) ; 
 int HDMI_CFG_422_EN ; 
 int HDMI_CFG_ESS_NOT_OESS ; 
 int HDMI_CFG_HDCP_EN ; 
 int HDMI_CFG_HDMI_NOT_DVI ; 
 int HDMI_CFG_H_SYNC_POL_NEG ; 
 int HDMI_CFG_V_SYNC_POL_NEG ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void hdmi_dbg_cfg(struct seq_file *s, int val)
{
	int tmp;

	seq_putc(s, '\t');
	tmp = val & HDMI_CFG_HDMI_NOT_DVI;
	DBGFS_PRINT_STR("mode:", tmp ? "HDMI" : "DVI");
	seq_puts(s, "\t\t\t\t\t");
	tmp = val & HDMI_CFG_HDCP_EN;
	DBGFS_PRINT_STR("HDCP:", tmp ? "enable" : "disable");
	seq_puts(s, "\t\t\t\t\t");
	tmp = val & HDMI_CFG_ESS_NOT_OESS;
	DBGFS_PRINT_STR("HDCP mode:", tmp ? "ESS enable" : "OESS enable");
	seq_puts(s, "\t\t\t\t\t");
	tmp = val & HDMI_CFG_H_SYNC_POL_NEG;
	DBGFS_PRINT_STR("Hsync polarity:", tmp ? "inverted" : "normal");
	seq_puts(s, "\t\t\t\t\t");
	tmp = val & HDMI_CFG_V_SYNC_POL_NEG;
	DBGFS_PRINT_STR("Vsync polarity:", tmp ? "inverted" : "normal");
	seq_puts(s, "\t\t\t\t\t");
	tmp = val & HDMI_CFG_422_EN;
	DBGFS_PRINT_STR("YUV422 format:", tmp ? "enable" : "disable");
}