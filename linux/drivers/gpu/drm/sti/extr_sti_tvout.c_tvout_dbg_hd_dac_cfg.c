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
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,char*) ; 

__attribute__((used)) static void tvout_dbg_hd_dac_cfg(struct seq_file *s, int val)
{
	seq_printf(s, "\t%-24s %s", "HD DAC:",
		   val & 1 ? "disabled" : "enabled");
}