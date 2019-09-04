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
struct pg_state {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (int /*<<< orphan*/ ,char*,char*,int,char const) ; 

__attribute__((used)) static int calculate_pagesize(struct pg_state *st, int ps, char s[])
{
	static const char units[] = "BKMGTPE";
	const char *unit = units;

	while (ps > 9 && unit[1]) {
		ps -= 10;
		unit++;
	}
	seq_printf(st->seq, "  %s_ps: %i%c\t", s, 1<<ps, *unit);
	return ps;
}