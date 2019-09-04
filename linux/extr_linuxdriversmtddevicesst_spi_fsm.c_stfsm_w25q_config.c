#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int seq_cfg; } ;
struct stfsm {TYPE_1__ stfsm_seq_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPINOR_OP_RDCR ; 
 int /*<<< orphan*/  SPINOR_OP_RDSR ; 
 int /*<<< orphan*/  SPINOR_OP_WRSR ; 
 int W25Q_STATUS_QE ; 
 int stfsm_prepare_rwe_seqs_default (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_read_status (struct stfsm*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stfsm_write_status (struct stfsm*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int stfsm_w25q_config(struct stfsm *fsm)
{
	uint32_t data_pads;
	uint8_t sr1, sr2;
	uint16_t sr_wr;
	int update_sr = 0;
	int ret;

	ret = stfsm_prepare_rwe_seqs_default(fsm);
	if (ret)
		return ret;

	/* Check status of 'QE' bit, update if required. */
	stfsm_read_status(fsm, SPINOR_OP_RDCR, &sr2, 1);
	data_pads = ((fsm->stfsm_seq_read.seq_cfg >> 16) & 0x3) + 1;
	if (data_pads == 4) {
		if (!(sr2 & W25Q_STATUS_QE)) {
			/* Set 'QE' */
			sr2 |= W25Q_STATUS_QE;
			update_sr = 1;
		}
	} else {
		if (sr2 & W25Q_STATUS_QE) {
			/* Clear 'QE' */
			sr2 &= ~W25Q_STATUS_QE;
			update_sr = 1;
		}
	}
	if (update_sr) {
		/* Write status register */
		stfsm_read_status(fsm, SPINOR_OP_RDSR, &sr1, 1);
		sr_wr = ((uint16_t)sr2 << 8) | sr1;
		stfsm_write_status(fsm, SPINOR_OP_WRSR, sr_wr, 2, 1);
	}

	return 0;
}