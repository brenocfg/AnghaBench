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
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 unsigned long const BIT (int) ; 
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char const* const) ; 

__attribute__((used)) static int blk_flags_show(struct seq_file *m, const unsigned long flags,
			  const char *const *flag_name, int flag_name_count)
{
	bool sep = false;
	int i;

	for (i = 0; i < sizeof(flags) * BITS_PER_BYTE; i++) {
		if (!(flags & BIT(i)))
			continue;
		if (sep)
			seq_puts(m, "|");
		sep = true;
		if (i < flag_name_count && flag_name[i])
			seq_puts(m, flag_name[i]);
		else
			seq_printf(m, "%d", i);
	}
	return 0;
}