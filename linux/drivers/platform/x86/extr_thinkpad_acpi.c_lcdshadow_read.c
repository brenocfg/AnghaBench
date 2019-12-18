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
 scalar_t__ lcdshadow_state ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int lcdshadow_read(struct seq_file *m)
{
	if (lcdshadow_state < 0) {
		seq_puts(m, "status:\t\tnot supported\n");
	} else {
		seq_printf(m, "status:\t\t%d\n", lcdshadow_state);
		seq_puts(m, "commands:\t0, 1\n");
	}

	return 0;
}