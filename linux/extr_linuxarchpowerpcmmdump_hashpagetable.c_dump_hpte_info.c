#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pg_state {int /*<<< orphan*/  seq; TYPE_1__* marker; } ;
struct TYPE_2__ {unsigned long start_address; unsigned long name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned long HPTE_V_AVPN_VAL (int /*<<< orphan*/ ) ; 
 int calculate_pagesize (struct pg_state*,int,char*) ; 
 int /*<<< orphan*/  dump_flag_info (struct pg_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_flag_array ; 
 int /*<<< orphan*/  seq_printf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  seq_putc (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  v_flag_array ; 

__attribute__((used)) static void dump_hpte_info(struct pg_state *st, unsigned long ea, u64 v, u64 r,
		unsigned long rpn, int bps, int aps, unsigned long lp)
{
	int aps_index;

	while (ea >= st->marker[1].start_address) {
		st->marker++;
		seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
	}
	seq_printf(st->seq, "0x%lx:\t", ea);
	seq_printf(st->seq, "AVPN:%llx\t", HPTE_V_AVPN_VAL(v));
	dump_flag_info(st, v_flag_array, v, ARRAY_SIZE(v_flag_array));
	seq_printf(st->seq, "  rpn: %lx\t", rpn);
	dump_flag_info(st, r_flag_array, r, ARRAY_SIZE(r_flag_array));

	calculate_pagesize(st, bps, "base");
	aps_index = calculate_pagesize(st, aps, "actual");
	if (aps_index != 2)
		seq_printf(st->seq, "LP enc: %lx", lp);
	seq_putc(st->seq, '\n');
}