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
struct stfsm {int /*<<< orphan*/  configuration; TYPE_1__ stfsm_seq_read; TYPE_1__ stfsm_seq_write; struct flash_info* info; } ;
struct flash_info {int flags; int sector_size; int n_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_S25FL_CHECK_ERROR_FLAGS ; 
 int FLASH_FLAG_32BIT_ADDR ; 
 int FLASH_FLAG_DYB_LOCKING ; 
 int /*<<< orphan*/  SPINOR_OP_RDCR ; 
 int /*<<< orphan*/  SPINOR_OP_RDSR ; 
 int /*<<< orphan*/  SPINOR_OP_WRSR ; 
 int STFSM_S25FL_CONFIG_QE ; 
 int stfsm_prepare_rwe_seqs_default (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_read_status (struct stfsm*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stfsm_s25fl_prepare_erasesec_seq_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stfsm_s25fl_read4_configs ; 
 int /*<<< orphan*/  stfsm_s25fl_read_dyb (struct stfsm*,int,int*) ; 
 int /*<<< orphan*/  stfsm_s25fl_write4_configs ; 
 int /*<<< orphan*/  stfsm_s25fl_write_dyb (struct stfsm*,int,int) ; 
 int stfsm_search_prepare_rw_seq (struct stfsm*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stfsm_seq_erase_sector ; 
 int /*<<< orphan*/  stfsm_write_status (struct stfsm*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int stfsm_s25fl_config(struct stfsm *fsm)
{
	struct flash_info *info = fsm->info;
	uint32_t flags = info->flags;
	uint32_t data_pads;
	uint32_t offs;
	uint16_t sta_wr;
	uint8_t sr1, cr1, dyb;
	int update_sr = 0;
	int ret;

	if (flags & FLASH_FLAG_32BIT_ADDR) {
		/*
		 * Prepare Read/Write/Erase sequences according to S25FLxxx
		 * 32-bit address command set
		 */
		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_read,
						  stfsm_s25fl_read4_configs);
		if (ret)
			return ret;

		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_write,
						  stfsm_s25fl_write4_configs);
		if (ret)
			return ret;

		stfsm_s25fl_prepare_erasesec_seq_32(&stfsm_seq_erase_sector);

	} else {
		/* Use default configurations for 24-bit addressing */
		ret = stfsm_prepare_rwe_seqs_default(fsm);
		if (ret)
			return ret;
	}

	/*
	 * For devices that support 'DYB' sector locking, check lock status and
	 * unlock sectors if necessary (some variants power-on with sectors
	 * locked by default)
	 */
	if (flags & FLASH_FLAG_DYB_LOCKING) {
		offs = 0;
		for (offs = 0; offs < info->sector_size * info->n_sectors;) {
			stfsm_s25fl_read_dyb(fsm, offs, &dyb);
			if (dyb == 0x00)
				stfsm_s25fl_write_dyb(fsm, offs, 0xff);

			/* Handle bottom/top 4KiB parameter sectors */
			if ((offs < info->sector_size * 2) ||
			    (offs >= (info->sector_size - info->n_sectors * 4)))
				offs += 0x1000;
			else
				offs += 0x10000;
		}
	}

	/* Check status of 'QE' bit, update if required. */
	stfsm_read_status(fsm, SPINOR_OP_RDCR, &cr1, 1);
	data_pads = ((fsm->stfsm_seq_read.seq_cfg >> 16) & 0x3) + 1;
	if (data_pads == 4) {
		if (!(cr1 & STFSM_S25FL_CONFIG_QE)) {
			/* Set 'QE' */
			cr1 |= STFSM_S25FL_CONFIG_QE;

			update_sr = 1;
		}
	} else {
		if (cr1 & STFSM_S25FL_CONFIG_QE) {
			/* Clear 'QE' */
			cr1 &= ~STFSM_S25FL_CONFIG_QE;

			update_sr = 1;
		}
	}
	if (update_sr) {
		stfsm_read_status(fsm, SPINOR_OP_RDSR, &sr1, 1);
		sta_wr = ((uint16_t)cr1  << 8) | sr1;
		stfsm_write_status(fsm, SPINOR_OP_WRSR, sta_wr, 2, 1);
	}

	/*
	 * S25FLxxx devices support Program and Error error flags.
	 * Configure driver to check flags and clear if necessary.
	 */
	fsm->configuration |= CFG_S25FL_CHECK_ERROR_FLAGS;

	return 0;
}