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
struct op_register_config {unsigned long reset_values; unsigned long proc_mode; unsigned long enable; } ;

/* Variables and functions */
 unsigned long wrperfmon (int,unsigned long) ; 

__attribute__((used)) static void
ev5_reset_ctr(struct op_register_config *reg, unsigned long ctr)
{
	unsigned long values, mask, not_pk, reset_values;

	mask = (ctr == 0 ? 0xfffful << 48
	        : ctr == 1 ? 0xfffful << 32
		: 0x3fff << 16);

	not_pk = 1 << 9 | 1 << 8;

	reset_values = reg->reset_values;

	if ((reg->proc_mode & not_pk) == not_pk) {
		values = wrperfmon(5, 0);
		values = (reset_values & mask) | (values & ~mask & -2);
		wrperfmon(6, values);
	} else {
		wrperfmon(0, -1);
		values = wrperfmon(5, 0);
		values = (reset_values & mask) | (values & ~mask & -2);
		wrperfmon(6, values);
		wrperfmon(1, reg->enable);
	}
}