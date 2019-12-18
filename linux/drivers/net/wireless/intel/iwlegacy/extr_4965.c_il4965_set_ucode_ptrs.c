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
struct TYPE_5__ {int p_addr; int len; } ;
struct TYPE_4__ {int len; } ;
struct TYPE_6__ {int p_addr; } ;
struct il_priv {TYPE_2__ ucode_code; TYPE_1__ ucode_data; TYPE_3__ ucode_data_backup; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSM_DRAM_DATA_BYTECOUNT_REG ; 
 int /*<<< orphan*/  BSM_DRAM_DATA_PTR_REG ; 
 int /*<<< orphan*/  BSM_DRAM_INST_BYTECOUNT_REG ; 
 int BSM_DRAM_INST_LOAD ; 
 int /*<<< orphan*/  BSM_DRAM_INST_PTR_REG ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
il4965_set_ucode_ptrs(struct il_priv *il)
{
	dma_addr_t pinst;
	dma_addr_t pdata;
	int ret = 0;

	/* bits 35:4 for 4965 */
	pinst = il->ucode_code.p_addr >> 4;
	pdata = il->ucode_data_backup.p_addr >> 4;

	/* Tell bootstrap uCode where to find image to load */
	il_wr_prph(il, BSM_DRAM_INST_PTR_REG, pinst);
	il_wr_prph(il, BSM_DRAM_DATA_PTR_REG, pdata);
	il_wr_prph(il, BSM_DRAM_DATA_BYTECOUNT_REG, il->ucode_data.len);

	/* Inst byte count must be last to set up, bit 31 signals uCode
	 *   that all new ptr/size info is in place */
	il_wr_prph(il, BSM_DRAM_INST_BYTECOUNT_REG,
		   il->ucode_code.len | BSM_DRAM_INST_LOAD);
	D_INFO("Runtime uCode pointers are set.\n");

	return ret;
}