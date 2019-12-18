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
struct stfsm_seq {int seq_cfg; int addr1; int addr2; int /*<<< orphan*/  data_size; } ;
struct stfsm {int configuration; scalar_t__ fifo_dir_delay; scalar_t__ base; int /*<<< orphan*/  dev; struct stfsm_seq stfsm_seq_write; } ;

/* Variables and functions */
 int CFG_S25FL_CHECK_ERROR_FLAGS ; 
 int CFG_WRITE_TOGGLE_32BIT_ADDR ; 
 int FLASH_PAGESIZE_32 ; 
 scalar_t__ SPI_FAST_SEQ_CFG ; 
 int /*<<< orphan*/  TRANSFER_SIZE (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  stfsm_enter_32bit_addr (struct stfsm*,int) ; 
 int /*<<< orphan*/  stfsm_load_seq (struct stfsm*,struct stfsm_seq*) ; 
 int /*<<< orphan*/  stfsm_s25fl_clear_status_reg (struct stfsm*) ; 
 int stfsm_wait_busy (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_wait_seq (struct stfsm*) ; 
 int /*<<< orphan*/  stfsm_write_fifo (struct stfsm*,int*,int) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int stfsm_write(struct stfsm *fsm, const uint8_t *buf,
		       uint32_t size, uint32_t offset)
{
	struct stfsm_seq *seq = &fsm->stfsm_seq_write;
	uint32_t data_pads;
	uint32_t write_mask;
	uint32_t size_ub;
	uint32_t size_lb;
	uint32_t size_mop;
	uint32_t tmp[4];
	uint32_t i;
	uint32_t page_buf[FLASH_PAGESIZE_32];
	uint8_t *t = (uint8_t *)&tmp;
	const uint8_t *p;
	int ret;

	dev_dbg(fsm->dev, "writing %d bytes to 0x%08x\n", size, offset);

	/* Enter 32-bit address mode, if required */
	if (fsm->configuration & CFG_WRITE_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 1);

	/* Must write in multiples of 32 cycles (or 32*pads/8 bytes) */
	data_pads = ((seq->seq_cfg >> 16) & 0x3) + 1;
	write_mask = (data_pads << 2) - 1;

	/* Handle non-aligned buf */
	if ((uintptr_t)buf & 0x3) {
		memcpy(page_buf, buf, size);
		p = (uint8_t *)page_buf;
	} else {
		p = buf;
	}

	/* Handle non-aligned size */
	size_ub = (size + write_mask) & ~write_mask;
	size_lb = size & ~write_mask;
	size_mop = size & write_mask;

	seq->data_size = TRANSFER_SIZE(size_ub);
	seq->addr1 = (offset >> 16) & 0xffff;
	seq->addr2 = offset & 0xffff;

	/* Need to set FIFO to write mode, before writing data to FIFO (see
	 * GNBvb79594)
	 */
	writel(0x00040000, fsm->base + SPI_FAST_SEQ_CFG);

	/*
	 * Before writing data to the FIFO, apply a small delay to allow a
	 * potential change of FIFO direction to complete.
	 */
	if (fsm->fifo_dir_delay == 0)
		readl(fsm->base + SPI_FAST_SEQ_CFG);
	else
		udelay(fsm->fifo_dir_delay);


	/* Write data to FIFO, before starting sequence (see GNBvd79593) */
	if (size_lb) {
		stfsm_write_fifo(fsm, (uint32_t *)p, size_lb);
		p += size_lb;
	}

	/* Handle non-aligned size */
	if (size_mop) {
		memset(t, 0xff, write_mask + 1);	/* fill with 0xff's */
		for (i = 0; i < size_mop; i++)
			t[i] = *p++;

		stfsm_write_fifo(fsm, tmp, write_mask + 1);
	}

	/* Start sequence */
	stfsm_load_seq(fsm, seq);

	/* Wait for sequence to finish */
	stfsm_wait_seq(fsm);

	/* Wait for completion */
	ret = stfsm_wait_busy(fsm);
	if (ret && fsm->configuration & CFG_S25FL_CHECK_ERROR_FLAGS)
		stfsm_s25fl_clear_status_reg(fsm);

	/* Exit 32-bit address mode, if required */
	if (fsm->configuration & CFG_WRITE_TOGGLE_32BIT_ADDR)
		stfsm_enter_32bit_addr(fsm, 0);

	return 0;
}