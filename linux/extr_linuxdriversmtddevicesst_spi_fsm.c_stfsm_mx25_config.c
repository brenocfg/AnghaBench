#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int seq_cfg; } ;
struct stfsm {int configuration; TYPE_2__ stfsm_seq_read; int /*<<< orphan*/  booted_from_spi; int /*<<< orphan*/  stfsm_seq_en_32bit_addr; TYPE_1__* info; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int CFG_ERASESEC_TOGGLE_32BIT_ADDR ; 
 int CFG_READ_TOGGLE_32BIT_ADDR ; 
 int CFG_WRITE_TOGGLE_32BIT_ADDR ; 
 int FLASH_FLAG_32BIT_ADDR ; 
 int MX25_STATUS_QE ; 
 int /*<<< orphan*/  SPINOR_OP_RDSR ; 
 int /*<<< orphan*/  SPINOR_OP_WRSR ; 
 int stfsm_can_handle_soc_reset (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_enter_32bit_addr (struct stfsm*,int) ; 
 int /*<<< orphan*/  stfsm_mx25_en_32bit_addr_seq (int /*<<< orphan*/ *) ; 
 int stfsm_prepare_rwe_seqs_default (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_read_status (struct stfsm*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stfsm_write_status (struct stfsm*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int stfsm_mx25_config(struct stfsm *fsm)
{
	uint32_t flags = fsm->info->flags;
	uint32_t data_pads;
	uint8_t sta;
	int ret;
	bool soc_reset;

	/*
	 * Use default READ/WRITE sequences
	 */
	ret = stfsm_prepare_rwe_seqs_default(fsm);
	if (ret)
		return ret;

	/*
	 * Configure 32-bit Address Support
	 */
	if (flags & FLASH_FLAG_32BIT_ADDR) {
		/* Configure 'enter_32bitaddr' FSM sequence */
		stfsm_mx25_en_32bit_addr_seq(&fsm->stfsm_seq_en_32bit_addr);

		soc_reset = stfsm_can_handle_soc_reset(fsm);
		if (soc_reset || !fsm->booted_from_spi)
			/* If we can handle SoC resets, we enable 32-bit address
			 * mode pervasively */
			stfsm_enter_32bit_addr(fsm, 1);

		else
			/* Else, enable/disable 32-bit addressing before/after
			 * each operation */
			fsm->configuration = (CFG_READ_TOGGLE_32BIT_ADDR |
					      CFG_WRITE_TOGGLE_32BIT_ADDR |
					      CFG_ERASESEC_TOGGLE_32BIT_ADDR);
	}

	/* Check status of 'QE' bit, update if required. */
	stfsm_read_status(fsm, SPINOR_OP_RDSR, &sta, 1);
	data_pads = ((fsm->stfsm_seq_read.seq_cfg >> 16) & 0x3) + 1;
	if (data_pads == 4) {
		if (!(sta & MX25_STATUS_QE)) {
			/* Set 'QE' */
			sta |= MX25_STATUS_QE;

			stfsm_write_status(fsm, SPINOR_OP_WRSR, sta, 1, 1);
		}
	} else {
		if (sta & MX25_STATUS_QE) {
			/* Clear 'QE' */
			sta &= ~MX25_STATUS_QE;

			stfsm_write_status(fsm, SPINOR_OP_WRSR, sta, 1, 1);
		}
	}

	return 0;
}