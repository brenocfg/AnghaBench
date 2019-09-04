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
struct thunderx_lmc {int /*<<< orphan*/  ring_tail; TYPE_1__* pdev; struct lmc_err_ctx* err_ctx; int /*<<< orphan*/  ring_head; } ;
struct mem_ctl_info {struct thunderx_lmc* pvt_info; } ;
struct lmc_err_ctx {int reg_int; int reg_fadr; int reg_nxm_fadr; int reg_scram_fadr; int reg_ecc_synd; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct lmc_err_ctx*) ; 
 scalar_t__ CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  LMC_FADR_FBANK (int) ; 
 int /*<<< orphan*/  LMC_FADR_FBUNK (int) ; 
 int /*<<< orphan*/  LMC_FADR_FCOL (int) ; 
 int /*<<< orphan*/  LMC_FADR_FDIMM (int) ; 
 int /*<<< orphan*/  LMC_FADR_FROW (int) ; 
 int LMC_INT_CE ; 
 int LMC_INT_UE ; 
 int /*<<< orphan*/  LMC_MESSAGE_SIZE ; 
 int /*<<< orphan*/  LMC_OTHER_SIZE ; 
 int /*<<< orphan*/  decode_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmc_errors ; 
 int /*<<< orphan*/  offset_in_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_pfn (int /*<<< orphan*/ ) ; 
 unsigned long ring_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thunderx_faddr_to_phys (int,struct thunderx_lmc*) ; 

__attribute__((used)) static irqreturn_t thunderx_lmc_threaded_isr(int irq, void *dev_id)
{
	struct mem_ctl_info *mci = dev_id;
	struct thunderx_lmc *lmc = mci->pvt_info;
	phys_addr_t phys_addr;

	unsigned long tail;
	struct lmc_err_ctx *ctx;

	irqreturn_t ret = IRQ_NONE;

	char *msg;
	char *other;

	msg = kmalloc(LMC_MESSAGE_SIZE, GFP_KERNEL);
	other =  kmalloc(LMC_OTHER_SIZE, GFP_KERNEL);

	if (!msg || !other)
		goto err_free;

	while (CIRC_CNT(lmc->ring_head, lmc->ring_tail,
		ARRAY_SIZE(lmc->err_ctx))) {
		tail = ring_pos(lmc->ring_tail, ARRAY_SIZE(lmc->err_ctx));

		ctx = &lmc->err_ctx[tail];

		dev_dbg(&lmc->pdev->dev, "LMC_INT: %016llx\n",
			ctx->reg_int);
		dev_dbg(&lmc->pdev->dev, "LMC_FADR: %016llx\n",
			ctx->reg_fadr);
		dev_dbg(&lmc->pdev->dev, "LMC_NXM_FADR: %016llx\n",
			ctx->reg_nxm_fadr);
		dev_dbg(&lmc->pdev->dev, "LMC_SCRAM_FADR: %016llx\n",
			ctx->reg_scram_fadr);
		dev_dbg(&lmc->pdev->dev, "LMC_ECC_SYND: %016llx\n",
			ctx->reg_ecc_synd);

		snprintf(msg, LMC_MESSAGE_SIZE,
			 "DIMM %lld rank %lld bank %lld row %lld col %lld",
			 LMC_FADR_FDIMM(ctx->reg_scram_fadr),
			 LMC_FADR_FBUNK(ctx->reg_scram_fadr),
			 LMC_FADR_FBANK(ctx->reg_scram_fadr),
			 LMC_FADR_FROW(ctx->reg_scram_fadr),
			 LMC_FADR_FCOL(ctx->reg_scram_fadr));

		decode_register(other, LMC_OTHER_SIZE, lmc_errors,
				ctx->reg_int);

		phys_addr = thunderx_faddr_to_phys(ctx->reg_fadr, lmc);

		if (ctx->reg_int & LMC_INT_UE)
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     phys_to_pfn(phys_addr),
					     offset_in_page(phys_addr),
					     0, -1, -1, -1, msg, other);
		else if (ctx->reg_int & LMC_INT_CE)
			edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
					     phys_to_pfn(phys_addr),
					     offset_in_page(phys_addr),
					     0, -1, -1, -1, msg, other);

		lmc->ring_tail++;
	}

	ret = IRQ_HANDLED;

err_free:
	kfree(msg);
	kfree(other);

	return ret;
}