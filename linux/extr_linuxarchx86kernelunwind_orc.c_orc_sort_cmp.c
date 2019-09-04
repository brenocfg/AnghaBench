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
struct orc_entry {scalar_t__ sp_reg; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 scalar_t__ ORC_REG_UNDEFINED ; 
 int const* cur_orc_ip_table ; 
 struct orc_entry* cur_orc_table ; 
 unsigned long orc_ip (int const*) ; 

__attribute__((used)) static int orc_sort_cmp(const void *_a, const void *_b)
{
	struct orc_entry *orc_a;
	const int *a = _a, *b = _b;
	unsigned long a_val = orc_ip(a);
	unsigned long b_val = orc_ip(b);

	if (a_val > b_val)
		return 1;
	if (a_val < b_val)
		return -1;

	/*
	 * The "weak" section terminator entries need to always be on the left
	 * to ensure the lookup code skips them in favor of real entries.
	 * These terminator entries exist to handle any gaps created by
	 * whitelisted .o files which didn't get objtool generation.
	 */
	orc_a = cur_orc_table + (a - cur_orc_ip_table);
	return orc_a->sp_reg == ORC_REG_UNDEFINED && !orc_a->end ? -1 : 1;
}