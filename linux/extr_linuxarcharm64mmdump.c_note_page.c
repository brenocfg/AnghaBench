#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct pg_state {unsigned int level; scalar_t__ current_prot; unsigned long start_address; TYPE_1__* marker; int /*<<< orphan*/  seq; } ;
struct TYPE_4__ {scalar_t__ mask; int /*<<< orphan*/  num; scalar_t__ bits; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {unsigned long start_address; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_prot (struct pg_state*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_prot_uxn (struct pg_state*,unsigned long) ; 
 int /*<<< orphan*/  note_prot_wx (struct pg_state*,unsigned long) ; 
 TYPE_2__* pg_level ; 
 int /*<<< orphan*/  pt_dump_seq_printf (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  pt_dump_seq_puts (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void note_page(struct pg_state *st, unsigned long addr, unsigned level,
				u64 val)
{
	static const char units[] = "KMGTPE";
	u64 prot = val & pg_level[level].mask;

	if (!st->level) {
		st->level = level;
		st->current_prot = prot;
		st->start_address = addr;
		pt_dump_seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
	} else if (prot != st->current_prot || level != st->level ||
		   addr >= st->marker[1].start_address) {
		const char *unit = units;
		unsigned long delta;

		if (st->current_prot) {
			note_prot_uxn(st, addr);
			note_prot_wx(st, addr);
			pt_dump_seq_printf(st->seq, "0x%016lx-0x%016lx   ",
				   st->start_address, addr);

			delta = (addr - st->start_address) >> 10;
			while (!(delta & 1023) && unit[1]) {
				delta >>= 10;
				unit++;
			}
			pt_dump_seq_printf(st->seq, "%9lu%c %s", delta, *unit,
				   pg_level[st->level].name);
			if (pg_level[st->level].bits)
				dump_prot(st, pg_level[st->level].bits,
					  pg_level[st->level].num);
			pt_dump_seq_puts(st->seq, "\n");
		}

		if (addr >= st->marker[1].start_address) {
			st->marker++;
			pt_dump_seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
		}

		st->start_address = addr;
		st->current_prot = prot;
		st->level = level;
	}

	if (addr >= st->marker[1].start_address) {
		st->marker++;
		pt_dump_seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
	}

}