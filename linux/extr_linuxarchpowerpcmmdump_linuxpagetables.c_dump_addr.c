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
struct pg_state {unsigned long start_address; int /*<<< orphan*/  seq; int /*<<< orphan*/  start_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 

__attribute__((used)) static void dump_addr(struct pg_state *st, unsigned long addr)
{
	static const char units[] = "KMGTPE";
	const char *unit = units;
	unsigned long delta;

#ifdef CONFIG_PPC64
	seq_printf(st->seq, "0x%016lx-0x%016lx ", st->start_address, addr-1);
	seq_printf(st->seq, "0x%016lx ", st->start_pa);
#else
	seq_printf(st->seq, "0x%08lx-0x%08lx ", st->start_address, addr - 1);
	seq_printf(st->seq, "0x%08lx ", st->start_pa);
#endif

	delta = (addr - st->start_address) >> 10;
	/* Work out what appropriate unit to use */
	while (!(delta & 1023) && unit[1]) {
		delta >>= 10;
		unit++;
	}
	seq_printf(st->seq, "%9lu%c", delta, *unit);

}