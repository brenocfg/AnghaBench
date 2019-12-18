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
struct stfsm_seq {int* seq_opc; int /*<<< orphan*/  seq_cfg; } ;
struct stfsm {int configuration; int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int CFG_S25FL_CHECK_ERROR_FLAGS ; 
 unsigned long FLASH_MAX_BUSY_WAIT ; 
 int FLASH_STATUS_BUSY ; 
 int /*<<< orphan*/  FLASH_STATUS_TIMEOUT ; 
 int S25FL_STATUS_E_ERR ; 
 int S25FL_STATUS_P_ERR ; 
 int SEQ_OPC_CYCLES (int) ; 
 int SEQ_OPC_OPCODE (int /*<<< orphan*/ ) ; 
 int SEQ_OPC_PADS_1 ; 
 int /*<<< orphan*/  SPINOR_OP_RDSR ; 
 scalar_t__ SPI_FAST_SEQ_CFG ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq*) ; 
 int /*<<< orphan*/  stfsm_read_fifo (struct stfsm*,int*,int) ; 
 struct stfsm_seq stfsm_seq_read_status_fifo ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint8_t stfsm_wait_busy(struct stfsm *fsm)
{
	struct stfsm_seq *seq = &stfsm_seq_read_status_fifo;
	unsigned long deadline;
	uint32_t status;
	int timeout = 0;

	/* Use RDRS1 */
	seq->seq_opc[0] = (SEQ_OPC_PADS_1 |
			   SEQ_OPC_CYCLES(8) |
			   SEQ_OPC_OPCODE(SPINOR_OP_RDSR));

	/* Load read_status sequence */
	stfsm_load_seq(fsm, seq);

	/*
	 * Repeat until busy bit is deasserted, or timeout, or error (S25FLxxxS)
	 */
	deadline = jiffies + FLASH_MAX_BUSY_WAIT;
	while (!timeout) {
		if (time_after_eq(jiffies, deadline))
			timeout = 1;

		stfsm_wait_seq(fsm);

		stfsm_read_fifo(fsm, &status, 4);

		if ((status & FLASH_STATUS_BUSY) == 0)
			return 0;

		if ((fsm->configuration & CFG_S25FL_CHECK_ERROR_FLAGS) &&
		    ((status & S25FL_STATUS_P_ERR) ||
		     (status & S25FL_STATUS_E_ERR)))
			return (uint8_t)(status & 0xff);

		if (!timeout)
			/* Restart */
			writel(seq->seq_cfg, fsm->base + SPI_FAST_SEQ_CFG);

		cond_resched();
	}

	dev_err(fsm->dev, "timeout on wait_busy\n");

	return FLASH_STATUS_TIMEOUT;
}