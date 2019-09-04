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
typedef  unsigned long long uint ;
typedef  unsigned long long u8 ;
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct sdma_engine {unsigned long long descq_phys; unsigned long long head_phys; int this_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_ADDR ; 
 int /*<<< orphan*/  CHECK_OPCODE ; 
 int /*<<< orphan*/  DESC_CNT ; 
 int /*<<< orphan*/  ENG_ERR_MASK ; 
 int /*<<< orphan*/  HEAD_ADDR ; 
 int /*<<< orphan*/  MEMORY ; 
 int /*<<< orphan*/  MEMORY_SDMA_MEMORY_CNT_SHIFT ; 
 int /*<<< orphan*/  MEMORY_SDMA_MEMORY_INDEX_SHIFT ; 
 unsigned long long OPCODE_CHECK_MASK_DISABLED ; 
 unsigned long long OPCODE_CHECK_VAL_DISABLED ; 
 int /*<<< orphan*/  RELOAD_CNT ; 
 unsigned long long SD (int /*<<< orphan*/ ) ; 
 unsigned long long SEND_CTXT_CHECK_OPCODE_MASK_SHIFT ; 
 unsigned long long SEND_CTXT_CHECK_OPCODE_VALUE_SHIFT ; 
 int /*<<< orphan*/  sdma_setlengen (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_update_tail (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sdma_integrity (struct sdma_engine*) ; 
 int /*<<< orphan*/  write_sde_csr (struct sdma_engine*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static void init_sdma_regs(
	struct sdma_engine *sde,
	u32 credits,
	uint idle_cnt)
{
	u8 opval, opmask;
#ifdef CONFIG_SDMA_VERBOSITY
	struct hfi1_devdata *dd = sde->dd;

	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__FILE__), __LINE__, __func__);
#endif

	write_sde_csr(sde, SD(BASE_ADDR), sde->descq_phys);
	sdma_setlengen(sde);
	sdma_update_tail(sde, 0); /* Set SendDmaTail */
	write_sde_csr(sde, SD(RELOAD_CNT), idle_cnt);
	write_sde_csr(sde, SD(DESC_CNT), 0);
	write_sde_csr(sde, SD(HEAD_ADDR), sde->head_phys);
	write_sde_csr(sde, SD(MEMORY),
		      ((u64)credits << SD(MEMORY_SDMA_MEMORY_CNT_SHIFT)) |
		      ((u64)(credits * sde->this_idx) <<
		       SD(MEMORY_SDMA_MEMORY_INDEX_SHIFT)));
	write_sde_csr(sde, SD(ENG_ERR_MASK), ~0ull);
	set_sdma_integrity(sde);
	opmask = OPCODE_CHECK_MASK_DISABLED;
	opval = OPCODE_CHECK_VAL_DISABLED;
	write_sde_csr(sde, SD(CHECK_OPCODE),
		      (opmask << SEND_CTXT_CHECK_OPCODE_MASK_SHIFT) |
		      (opval << SEND_CTXT_CHECK_OPCODE_VALUE_SHIFT));
}