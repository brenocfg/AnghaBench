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
typedef  unsigned long long u64 ;
struct seq_file {int dummy; } ;
struct field_desc {unsigned long long width; unsigned long long start; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void field_desc_show(struct seq_file *seq, u64 v,
			    const struct field_desc *p)
{
	char buf[32];
	int line_size = 0;

	while (p->name) {
		u64 mask = (1ULL << p->width) - 1;
		int len = scnprintf(buf, sizeof(buf), "%s: %llu", p->name,
				    ((unsigned long long)v >> p->start) & mask);

		if (line_size + len >= 79) {
			line_size = 8;
			seq_puts(seq, "\n        ");
		}
		seq_printf(seq, "%s ", buf);
		line_size += len + 1;
		p++;
	}
	seq_putc(seq, '\n');
}