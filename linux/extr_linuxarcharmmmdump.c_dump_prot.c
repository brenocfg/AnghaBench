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
struct prot_bits {int mask; int val; char* set; char* clear; } ;
struct pg_state {int current_prot; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_dump_seq_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void dump_prot(struct pg_state *st, const struct prot_bits *bits, size_t num)
{
	unsigned i;

	for (i = 0; i < num; i++, bits++) {
		const char *s;

		if ((st->current_prot & bits->mask) == bits->val)
			s = bits->set;
		else
			s = bits->clear;

		if (s)
			pt_dump_seq_printf(st->seq, " %s", s);
	}
}