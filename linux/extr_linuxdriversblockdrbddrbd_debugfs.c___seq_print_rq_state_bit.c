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
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char const*) ; 

__attribute__((used)) static void __seq_print_rq_state_bit(struct seq_file *m,
	bool is_set, char *sep, const char *set_name, const char *unset_name)
{
	if (is_set && set_name) {
		seq_putc(m, *sep);
		seq_puts(m, set_name);
		*sep = '|';
	} else if (!is_set && unset_name) {
		seq_putc(m, *sep);
		seq_puts(m, unset_name);
		*sep = '|';
	}
}