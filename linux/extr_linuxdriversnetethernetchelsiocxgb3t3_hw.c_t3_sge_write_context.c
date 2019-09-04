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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTEXT_CMD ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK0 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK1 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK2 ; 
 int /*<<< orphan*/  A_SG_CONTEXT_MASK3 ; 
 int /*<<< orphan*/  F_CONTEXT_CMD_BUSY ; 
 unsigned int F_RESPONSEQ ; 
 int /*<<< orphan*/  SG_CONTEXT_CMD_ATTEMPTS ; 
 unsigned int V_CONTEXT (unsigned int) ; 
 unsigned int V_CONTEXT_CMD_OPCODE (int) ; 
 int t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int t3_sge_write_context(struct adapter *adapter, unsigned int id,
				unsigned int type)
{
	if (type == F_RESPONSEQ) {
		/*
		 * Can't write the Response Queue Context bits for
		 * Interrupt Armed or the Reserve bits after the chip
		 * has been initialized out of reset.  Writing to these
		 * bits can confuse the hardware.
		 */
		t3_write_reg(adapter, A_SG_CONTEXT_MASK0, 0xffffffff);
		t3_write_reg(adapter, A_SG_CONTEXT_MASK1, 0xffffffff);
		t3_write_reg(adapter, A_SG_CONTEXT_MASK2, 0x17ffffff);
		t3_write_reg(adapter, A_SG_CONTEXT_MASK3, 0xffffffff);
	} else {
		t3_write_reg(adapter, A_SG_CONTEXT_MASK0, 0xffffffff);
		t3_write_reg(adapter, A_SG_CONTEXT_MASK1, 0xffffffff);
		t3_write_reg(adapter, A_SG_CONTEXT_MASK2, 0xffffffff);
		t3_write_reg(adapter, A_SG_CONTEXT_MASK3, 0xffffffff);
	}
	t3_write_reg(adapter, A_SG_CONTEXT_CMD,
		     V_CONTEXT_CMD_OPCODE(1) | type | V_CONTEXT(id));
	return t3_wait_op_done(adapter, A_SG_CONTEXT_CMD, F_CONTEXT_CMD_BUSY,
			       0, SG_CONTEXT_CMD_ATTEMPTS, 1);
}