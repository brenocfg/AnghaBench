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
typedef  int /*<<< orphan*/  uint32_t ;
struct stfsm_seq {int* seq_opc; } ;
struct stfsm {struct stfsm_seq stfsm_seq_en_32bit_addr; } ;

/* Variables and functions */
 int SEQ_OPC_CSDEASSERT ; 
 int SEQ_OPC_CYCLES (int) ; 
 int SEQ_OPC_OPCODE (int /*<<< orphan*/ ) ; 
 int SEQ_OPC_PADS_1 ; 
 int /*<<< orphan*/  SPINOR_OP_EN4B ; 
 int /*<<< orphan*/  SPINOR_OP_EX4B ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq*) ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 

__attribute__((used)) static int stfsm_enter_32bit_addr(struct stfsm *fsm, int enter)
{
	struct stfsm_seq *seq = &fsm->stfsm_seq_en_32bit_addr;
	uint32_t cmd = enter ? SPINOR_OP_EN4B : SPINOR_OP_EX4B;

	seq->seq_opc[0] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(cmd) |
			   SEQ_OPC_CSDEASSERT);

	stfsm_load_seq(fsm, seq);

	stfsm_wait_seq(fsm);

	return 0;
}