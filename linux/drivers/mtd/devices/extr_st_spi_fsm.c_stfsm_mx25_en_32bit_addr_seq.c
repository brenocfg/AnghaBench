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
struct stfsm_seq {int* seq_opc; int seq_cfg; int /*<<< orphan*/ * seq; } ;

/* Variables and functions */
 int SEQ_CFG_CSDEASSERT ; 
 int SEQ_CFG_ERASE ; 
 int SEQ_CFG_PADS_1 ; 
 int SEQ_CFG_READNOTWRITE ; 
 int SEQ_CFG_STARTSEQ ; 
 int SEQ_OPC_CSDEASSERT ; 
 int SEQ_OPC_CYCLES (int) ; 
 int SEQ_OPC_OPCODE (int /*<<< orphan*/ ) ; 
 int SEQ_OPC_PADS_1 ; 
 int /*<<< orphan*/  SPINOR_OP_EN4B ; 
 int /*<<< orphan*/  STFSM_INST_CMD1 ; 
 int /*<<< orphan*/  STFSM_INST_STOP ; 
 int /*<<< orphan*/  STFSM_INST_WAIT ; 

__attribute__((used)) static int stfsm_mx25_en_32bit_addr_seq(struct stfsm_seq *seq)
{
	seq->seq_opc[0] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(SPINOR_OP_EN4B) |
			   SEQ_OPC_CSDEASSERT);

	seq->seq[0] = STFSM_INST_CMD1;
	seq->seq[1] = STFSM_INST_WAIT;
	seq->seq[2] = STFSM_INST_STOP;

	seq->seq_cfg = (SEQ_CFG_PADS_1 |
			SEQ_CFG_ERASE |
			SEQ_CFG_READNOTWRITE |
			SEQ_CFG_CSDEASSERT |
			SEQ_CFG_STARTSEQ);

	return 0;
}