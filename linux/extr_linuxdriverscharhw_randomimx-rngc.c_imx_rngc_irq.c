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
typedef  int u32 ;
struct imx_rngc {int /*<<< orphan*/  rng_op_done; scalar_t__ base; void* err_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RNGC_ERROR ; 
 scalar_t__ RNGC_STATUS ; 
 int RNGC_STATUS_SEED_DONE ; 
 int RNGC_STATUS_ST_DONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imx_rngc_irq_mask_clear (struct imx_rngc*) ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static irqreturn_t imx_rngc_irq(int irq, void *priv)
{
	struct imx_rngc *rngc = (struct imx_rngc *)priv;
	u32 status;

	/*
	 * clearing the interrupt will also clear the error register
	 * read error and status before clearing
	 */
	status = readl(rngc->base + RNGC_STATUS);
	rngc->err_reg = readl(rngc->base + RNGC_ERROR);

	imx_rngc_irq_mask_clear(rngc);

	if (status & (RNGC_STATUS_SEED_DONE | RNGC_STATUS_ST_DONE))
		complete(&rngc->rng_op_done);

	return IRQ_HANDLED;
}