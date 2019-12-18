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
typedef  size_t u8 ;
struct hva_dev {int sts_reg; int sfl_reg; int lmi_err_reg; int emi_err_reg; int hec_mif_err_reg; int /*<<< orphan*/  interrupt; struct hva_ctx** instances; } ;
struct hva_ctx {int hw_err; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t HVA_MAX_INSTANCES ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,size_t) ; 
 struct device* hva_to_dev (struct hva_dev*) ; 

__attribute__((used)) static irqreturn_t hva_hw_err_irq_thread(int irq, void *arg)
{
	struct hva_dev *hva = arg;
	struct device *dev = hva_to_dev(hva);
	u8 ctx_id = 0;
	struct hva_ctx *ctx;

	dev_dbg(dev, "%s     status: 0x%02x fifo level: 0x%02x\n",
		HVA_PREFIX, hva->sts_reg & 0xFF, hva->sfl_reg & 0xF);

	/*
	 * status: task_id[31:16] client_id[15:8] status[7:0]
	 * the context identifier is retrieved from the client identifier
	 */
	ctx_id = (hva->sts_reg & 0xFF00) >> 8;
	if (ctx_id >= HVA_MAX_INSTANCES) {
		dev_err(dev, "%s     bad context identifier: %d\n", HVA_PREFIX,
			ctx_id);
		goto out;
	}

	ctx = hva->instances[ctx_id];
	if (!ctx)
		goto out;

	if (hva->lmi_err_reg) {
		dev_err(dev, "%s     local memory interface error: 0x%08x\n",
			ctx->name, hva->lmi_err_reg);
		ctx->hw_err = true;
	}

	if (hva->emi_err_reg) {
		dev_err(dev, "%s     external memory interface error: 0x%08x\n",
			ctx->name, hva->emi_err_reg);
		ctx->hw_err = true;
	}

	if (hva->hec_mif_err_reg) {
		dev_err(dev, "%s     hec memory interface error: 0x%08x\n",
			ctx->name, hva->hec_mif_err_reg);
		ctx->hw_err = true;
	}
out:
	complete(&hva->interrupt);

	return IRQ_HANDLED;
}