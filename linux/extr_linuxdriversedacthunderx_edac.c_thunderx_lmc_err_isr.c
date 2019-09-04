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
struct thunderx_lmc {scalar_t__ regs; int /*<<< orphan*/  ecc_int; int /*<<< orphan*/  ring_head; struct lmc_err_ctx* err_ctx; } ;
struct mem_ctl_info {struct thunderx_lmc* pvt_info; } ;
struct lmc_err_ctx {int reg_int; void* reg_ecc_synd; void* reg_scram_fadr; void* reg_nxm_fadr; void* reg_fadr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct lmc_err_ctx*) ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 scalar_t__ LMC_CHAR_MASK0 ; 
 scalar_t__ LMC_CHAR_MASK2 ; 
 scalar_t__ LMC_ECC_PARITY_TEST ; 
 scalar_t__ LMC_ECC_SYND ; 
 scalar_t__ LMC_FADR ; 
 scalar_t__ LMC_INT ; 
 scalar_t__ LMC_NXM_FADR ; 
 scalar_t__ LMC_SCRAM_FADR ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 void* readq (scalar_t__) ; 
 unsigned long ring_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t thunderx_lmc_err_isr(int irq, void *dev_id)
{
	struct mem_ctl_info *mci = dev_id;
	struct thunderx_lmc *lmc = mci->pvt_info;

	unsigned long head = ring_pos(lmc->ring_head, ARRAY_SIZE(lmc->err_ctx));
	struct lmc_err_ctx *ctx = &lmc->err_ctx[head];

	writeq(0, lmc->regs + LMC_CHAR_MASK0);
	writeq(0, lmc->regs + LMC_CHAR_MASK2);
	writeq(0x2, lmc->regs + LMC_ECC_PARITY_TEST);

	ctx->reg_int = readq(lmc->regs + LMC_INT);
	ctx->reg_fadr = readq(lmc->regs + LMC_FADR);
	ctx->reg_nxm_fadr = readq(lmc->regs + LMC_NXM_FADR);
	ctx->reg_scram_fadr = readq(lmc->regs + LMC_SCRAM_FADR);
	ctx->reg_ecc_synd = readq(lmc->regs + LMC_ECC_SYND);

	lmc->ring_head++;

	atomic_set(&lmc->ecc_int, 1);

	/* Clear the interrupt */
	writeq(ctx->reg_int, lmc->regs + LMC_INT);

	return IRQ_WAKE_THREAD;
}