#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ p_addr; scalar_t__ len; } ;
struct TYPE_5__ {scalar_t__ p_addr; scalar_t__ len; } ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/ * v_addr; } ;
struct il_priv {TYPE_3__ ucode_init_data; TYPE_2__ ucode_init; TYPE_1__ ucode_boot; } ;
typedef  scalar_t__ dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BSM_DRAM_DATA_BYTECOUNT_REG ; 
 int /*<<< orphan*/  BSM_DRAM_DATA_PTR_REG ; 
 int /*<<< orphan*/  BSM_DRAM_INST_BYTECOUNT_REG ; 
 int /*<<< orphan*/  BSM_DRAM_INST_PTR_REG ; 
 scalar_t__ BSM_SRAM_LOWER_BOUND ; 
 int /*<<< orphan*/  BSM_WR_CTRL_REG ; 
 scalar_t__ BSM_WR_CTRL_REG_BIT_START ; 
 scalar_t__ BSM_WR_CTRL_REG_BIT_START_EN ; 
 int /*<<< orphan*/  BSM_WR_DWCOUNT_REG ; 
 int /*<<< orphan*/  BSM_WR_MEM_DST_REG ; 
 int /*<<< orphan*/  BSM_WR_MEM_SRC_REG ; 
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ IL39_MAX_BSM_SIZE ; 
 scalar_t__ IL39_RTC_INST_LOWER_BOUND ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  _il_wr_prph (struct il_priv*,scalar_t__,int /*<<< orphan*/ ) ; 
 int il3945_verify_bsm (struct il_priv*) ; 
 scalar_t__ il_rd_prph (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
il3945_load_bsm(struct il_priv *il)
{
	__le32 *image = il->ucode_boot.v_addr;
	u32 len = il->ucode_boot.len;
	dma_addr_t pinst;
	dma_addr_t pdata;
	u32 inst_len;
	u32 data_len;
	int rc;
	int i;
	u32 done;
	u32 reg_offset;

	D_INFO("Begin load bsm\n");

	/* make sure bootstrap program is no larger than BSM's SRAM size */
	if (len > IL39_MAX_BSM_SIZE)
		return -EINVAL;

	/* Tell bootstrap uCode where to find the "Initialize" uCode
	 *   in host DRAM ... host DRAM physical address bits 31:0 for 3945.
	 * NOTE:  il3945_initialize_alive_start() will replace these values,
	 *        after the "initialize" uCode has run, to point to
	 *        runtime/protocol instructions and backup data cache. */
	pinst = il->ucode_init.p_addr;
	pdata = il->ucode_init_data.p_addr;
	inst_len = il->ucode_init.len;
	data_len = il->ucode_init_data.len;

	il_wr_prph(il, BSM_DRAM_INST_PTR_REG, pinst);
	il_wr_prph(il, BSM_DRAM_DATA_PTR_REG, pdata);
	il_wr_prph(il, BSM_DRAM_INST_BYTECOUNT_REG, inst_len);
	il_wr_prph(il, BSM_DRAM_DATA_BYTECOUNT_REG, data_len);

	/* Fill BSM memory with bootstrap instructions */
	for (reg_offset = BSM_SRAM_LOWER_BOUND;
	     reg_offset < BSM_SRAM_LOWER_BOUND + len;
	     reg_offset += sizeof(u32), image++)
		_il_wr_prph(il, reg_offset, le32_to_cpu(*image));

	rc = il3945_verify_bsm(il);
	if (rc)
		return rc;

	/* Tell BSM to copy from BSM SRAM into instruction SRAM, when asked */
	il_wr_prph(il, BSM_WR_MEM_SRC_REG, 0x0);
	il_wr_prph(il, BSM_WR_MEM_DST_REG, IL39_RTC_INST_LOWER_BOUND);
	il_wr_prph(il, BSM_WR_DWCOUNT_REG, len / sizeof(u32));

	/* Load bootstrap code into instruction SRAM now,
	 *   to prepare to load "initialize" uCode */
	il_wr_prph(il, BSM_WR_CTRL_REG, BSM_WR_CTRL_REG_BIT_START);

	/* Wait for load of bootstrap uCode to finish */
	for (i = 0; i < 100; i++) {
		done = il_rd_prph(il, BSM_WR_CTRL_REG);
		if (!(done & BSM_WR_CTRL_REG_BIT_START))
			break;
		udelay(10);
	}
	if (i < 100)
		D_INFO("BSM write complete, poll %d iterations\n", i);
	else {
		IL_ERR("BSM write did not complete!\n");
		return -EIO;
	}

	/* Enable future boot loads whenever power management unit triggers it
	 *   (e.g. when powering back up after power-save shutdown) */
	il_wr_prph(il, BSM_WR_CTRL_REG, BSM_WR_CTRL_REG_BIT_START_EN);

	return 0;
}