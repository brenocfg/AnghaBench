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
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char* const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void mixer_dbg_ctl(struct seq_file *s, int val)
{
	unsigned int i;
	int count = 0;
	char *const disp_layer[] = {"BKG", "VID0", "VID1", "GDP0",
				    "GDP1", "GDP2", "GDP3"};

	seq_puts(s, "\tEnabled: ");
	for (i = 0; i < 7; i++) {
		if (val & 1) {
			seq_printf(s, "%s ", disp_layer[i]);
			count++;
		}
		val = val >> 1;
	}

	val = val >> 2;
	if (val & 1) {
		seq_puts(s, "CURS ");
		count++;
	}
	if (!count)
		seq_puts(s, "Nothing");
}