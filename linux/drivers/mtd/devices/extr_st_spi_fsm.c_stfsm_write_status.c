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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct stfsm_seq {int* seq_opc; int status; int /*<<< orphan*/ * seq; } ;
struct stfsm {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int SEQ_OPC_CYCLES (int) ; 
 int SEQ_OPC_OPCODE (int /*<<< orphan*/ ) ; 
 int SEQ_OPC_PADS_1 ; 
 int STA_CSDEASSERT ; 
 int STA_PADS_1 ; 
 int /*<<< orphan*/  STFSM_INST_STA_WR1 ; 
 int /*<<< orphan*/  STFSM_INST_STA_WR1_2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq*) ; 
 struct stfsm_seq stfsm_seq_write_status ; 
 int /*<<< orphan*/  stfsm_wait_busy (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 

__attribute__((used)) static int stfsm_write_status(struct stfsm *fsm, uint8_t cmd,
			    uint16_t data, int bytes, int wait_busy)
{
	struct stfsm_seq *seq = &stfsm_seq_write_status;

	dev_dbg(fsm->dev,
		"write 'status' register [0x%02x], %d byte(s), 0x%04x\n"
		" %s wait-busy\n", cmd, bytes, data, wait_busy ? "with" : "no");

	BUG_ON(bytes != 1 && bytes != 2);

	seq->seq_opc[1] = (SEQ_OPC_PADS_1 | SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(cmd));

	seq->status = (uint32_t)data | STA_PADS_1 | STA_CSDEASSERT;
	seq->seq[2] = (bytes == 1) ? STFSM_INST_STA_WR1 : STFSM_INST_STA_WR1_2;

	stfsm_load_seq(fsm, seq);

	stfsm_wait_seq(fsm);

	if (wait_busy)
		stfsm_wait_busy(fsm);

	return 0;
}