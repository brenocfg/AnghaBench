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
struct fixup_entry {unsigned long mask; unsigned long value; int /*<<< orphan*/  alt_end_off; int /*<<< orphan*/  alt_start_off; int /*<<< orphan*/  end_off; int /*<<< orphan*/  start_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_INST_NOP ; 
 unsigned int* calc_addr (struct fixup_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ patch_alt_instruction (unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  raw_patch_instruction (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_feature_section(unsigned long value, struct fixup_entry *fcur)
{
	unsigned int *start, *end, *alt_start, *alt_end, *src, *dest;

	start = calc_addr(fcur, fcur->start_off);
	end = calc_addr(fcur, fcur->end_off);
	alt_start = calc_addr(fcur, fcur->alt_start_off);
	alt_end = calc_addr(fcur, fcur->alt_end_off);

	if ((alt_end - alt_start) > (end - start))
		return 1;

	if ((value & fcur->mask) == fcur->value)
		return 0;

	src = alt_start;
	dest = start;

	for (; src < alt_end; src++, dest++) {
		if (patch_alt_instruction(src, dest, alt_start, alt_end))
			return 1;
	}

	for (; dest < end; dest++)
		raw_patch_instruction(dest, PPC_INST_NOP);

	return 0;
}