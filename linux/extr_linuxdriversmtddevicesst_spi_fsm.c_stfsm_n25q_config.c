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
struct stfsm {int configuration; int /*<<< orphan*/  booted_from_spi; int /*<<< orphan*/  stfsm_seq_en_32bit_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  stfsm_seq_write; int /*<<< orphan*/  stfsm_seq_read; TYPE_1__* info; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CFG_ERASESEC_TOGGLE_32BIT_ADDR ; 
 int CFG_WRITE_TOGGLE_32BIT_ADDR ; 
 int FLASH_FLAG_32BIT_ADDR ; 
 int /*<<< orphan*/  N25Q_CMD_WRVCR ; 
 int N25Q_VCR_DUMMY_CYCLES (int) ; 
 int N25Q_VCR_WRAP_CONT ; 
 int N25Q_VCR_XIP_DISABLED ; 
 int /*<<< orphan*/  default_write_configs ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  n25q_read3_configs ; 
 int /*<<< orphan*/  n25q_read4_configs ; 
 int stfsm_can_handle_soc_reset (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_enter_32bit_addr (struct stfsm*,int) ; 
 int /*<<< orphan*/  stfsm_n25q_en_32bit_addr_seq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stfsm_prepare_erasesec_seq (struct stfsm*,int /*<<< orphan*/ *) ; 
 int stfsm_search_prepare_rw_seq (struct stfsm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stfsm_seq_erase_sector ; 
 int /*<<< orphan*/  stfsm_write_status (struct stfsm*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stfsm_n25q_config(struct stfsm *fsm)
{
	uint32_t flags = fsm->info->flags;
	uint8_t vcr;
	int ret = 0;
	bool soc_reset;

	/* Configure 'READ' sequence */
	if (flags & FLASH_FLAG_32BIT_ADDR)
		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_read,
						  n25q_read4_configs);
	else
		ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_read,
						  n25q_read3_configs);
	if (ret) {
		dev_err(fsm->dev,
			"failed to prepare READ sequence with flags [0x%08x]\n",
			flags);
		return ret;
	}

	/* Configure 'WRITE' sequence (default configs) */
	ret = stfsm_search_prepare_rw_seq(fsm, &fsm->stfsm_seq_write,
					  default_write_configs);
	if (ret) {
		dev_err(fsm->dev,
			"preparing WRITE sequence using flags [0x%08x] failed\n",
			flags);
		return ret;
	}

	/* * Configure 'ERASE_SECTOR' sequence */
	stfsm_prepare_erasesec_seq(fsm, &stfsm_seq_erase_sector);

	/* Configure 32-bit address support */
	if (flags & FLASH_FLAG_32BIT_ADDR) {
		stfsm_n25q_en_32bit_addr_seq(&fsm->stfsm_seq_en_32bit_addr);

		soc_reset = stfsm_can_handle_soc_reset(fsm);
		if (soc_reset || !fsm->booted_from_spi) {
			/*
			 * If we can handle SoC resets, we enable 32-bit
			 * address mode pervasively
			 */
			stfsm_enter_32bit_addr(fsm, 1);
		} else {
			/*
			 * If not, enable/disable for WRITE and ERASE
			 * operations (READ uses special commands)
			 */
			fsm->configuration = (CFG_WRITE_TOGGLE_32BIT_ADDR |
					      CFG_ERASESEC_TOGGLE_32BIT_ADDR);
		}
	}

	/*
	 * Configure device to use 8 dummy cycles
	 */
	vcr = (N25Q_VCR_DUMMY_CYCLES(8) | N25Q_VCR_XIP_DISABLED |
	       N25Q_VCR_WRAP_CONT);
	stfsm_write_status(fsm, N25Q_CMD_WRVCR, vcr, 1, 0);

	return 0;
}