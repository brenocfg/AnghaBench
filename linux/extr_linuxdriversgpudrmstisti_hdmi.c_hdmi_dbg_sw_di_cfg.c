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
 int /*<<< orphan*/  DBGFS_PRINT_STR (char*,char* const) ; 
 int HDMI_IFRAME_CFG_DI_N (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HDMI_IFRAME_MASK ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void hdmi_dbg_sw_di_cfg(struct seq_file *s, int val)
{
	int tmp;
	char *const en_di[] = {"no transmission",
			       "single transmission",
			       "once every field",
			       "once every frame"};

	seq_putc(s, '\t');
	tmp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 1));
	DBGFS_PRINT_STR("Data island 1:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 2)) >> 4;
	DBGFS_PRINT_STR("Data island 2:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 3)) >> 8;
	DBGFS_PRINT_STR("Data island 3:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 4)) >> 12;
	DBGFS_PRINT_STR("Data island 4:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 5)) >> 16;
	DBGFS_PRINT_STR("Data island 5:", en_di[tmp]);
	seq_puts(s, "\t\t\t\t\t");
	tmp = (val & HDMI_IFRAME_CFG_DI_N(HDMI_IFRAME_MASK, 6)) >> 20;
	DBGFS_PRINT_STR("Data island 6:", en_di[tmp]);
}