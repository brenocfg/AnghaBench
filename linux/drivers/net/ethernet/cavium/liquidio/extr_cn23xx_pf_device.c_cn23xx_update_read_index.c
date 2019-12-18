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
typedef  int u32 ;
struct octeon_instr_queue {int pkt_in_done; int max_count; int /*<<< orphan*/  octeon_read_index; int /*<<< orphan*/  inst_cnt_reg; } ;

/* Variables and functions */
 int CN23XX_PKT_IN_DONE_CNT_MASK ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cn23xx_update_read_index(struct octeon_instr_queue *iq)
{
	u32 new_idx;
	u32 last_done;
	u32 pkt_in_done = readl(iq->inst_cnt_reg);

	last_done = pkt_in_done - iq->pkt_in_done;
	iq->pkt_in_done = pkt_in_done;

	/* Modulo of the new index with the IQ size will give us
	 * the new index.  The iq->reset_instr_cnt is always zero for
	 * cn23xx, so no extra adjustments are needed.
	 */
	new_idx = (iq->octeon_read_index +
		   (u32)(last_done & CN23XX_PKT_IN_DONE_CNT_MASK)) %
		  iq->max_count;

	return new_idx;
}