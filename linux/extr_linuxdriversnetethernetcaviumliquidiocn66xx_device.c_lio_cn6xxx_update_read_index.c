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
typedef  scalar_t__ u32 ;
struct octeon_instr_queue {scalar_t__ max_count; scalar_t__ reset_instr_cnt; int /*<<< orphan*/  inst_cnt_reg; } ;

/* Variables and functions */
 scalar_t__ readl (int /*<<< orphan*/ ) ; 

u32
lio_cn6xxx_update_read_index(struct octeon_instr_queue *iq)
{
	u32 new_idx = readl(iq->inst_cnt_reg);

	/* The new instr cnt reg is a 32-bit counter that can roll over. We have
	 * noted the counter's initial value at init time into
	 * reset_instr_cnt
	 */
	if (iq->reset_instr_cnt < new_idx)
		new_idx -= iq->reset_instr_cnt;
	else
		new_idx += (0xffffffff - iq->reset_instr_cnt) + 1;

	/* Modulo of the new index with the IQ size will give us
	 * the new index.
	 */
	new_idx %= iq->max_count;

	return new_idx;
}