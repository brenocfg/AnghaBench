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
 int HDMI_STA_DLL_LCK ; 
 int HDMI_STA_HOT_PLUG ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void hdmi_dbg_sta(struct seq_file *s, int val)
{
	int tmp;

	seq_putc(s, '\t');
	tmp = (val & HDMI_STA_DLL_LCK);
	DBGFS_PRINT_STR("pll:", tmp ? "locked" : "not locked");
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & HDMI_STA_HOT_PLUG);
	DBGFS_PRINT_STR("hdmi cable:", tmp ? "connected" : "not connected");
}