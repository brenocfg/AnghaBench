#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_3__ {int format; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int WAIT_NEXT_VSYNC ; 
 TYPE_1__* gdp_format_to_str ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void gdp_dbg_ctl(struct seq_file *s, int val)
{
	int i;

	seq_puts(s, "\tColor:");
	for (i = 0; i < ARRAY_SIZE(gdp_format_to_str); i++) {
		if (gdp_format_to_str[i].format == (val & 0x1F)) {
			seq_puts(s, gdp_format_to_str[i].name);
			break;
		}
	}
	if (i == ARRAY_SIZE(gdp_format_to_str))
		seq_puts(s, "<UNKNOWN>");

	seq_printf(s, "\tWaitNextVsync:%d", val & WAIT_NEXT_VSYNC ? 1 : 0);
}