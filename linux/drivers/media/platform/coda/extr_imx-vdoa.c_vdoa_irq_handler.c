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
struct vdoa_data {int /*<<< orphan*/  dev; scalar_t__ regs; struct vdoa_ctx* curr_ctx; } ;
struct vdoa_ctx {int /*<<< orphan*/  completion; int /*<<< orphan*/  completed_job; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ VDOAIE ; 
 scalar_t__ VDOAIST ; 
 int VDOAIST_EOT ; 
 int VDOAIST_TERR ; 
 scalar_t__ VDOASR ; 
 int VDOASR_ERRW ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t vdoa_irq_handler(int irq, void *data)
{
	struct vdoa_data *vdoa = data;
	struct vdoa_ctx *curr_ctx;
	u32 val;

	/* Disable interrupts */
	writel(0, vdoa->regs + VDOAIE);

	curr_ctx = vdoa->curr_ctx;
	if (!curr_ctx) {
		dev_warn(vdoa->dev,
			"Instance released before the end of transaction\n");
		return IRQ_HANDLED;
	}

	val = readl(vdoa->regs + VDOAIST);
	writel(val, vdoa->regs + VDOAIST);
	if (val & VDOAIST_TERR) {
		val = readl(vdoa->regs + VDOASR) & VDOASR_ERRW;
		dev_err(vdoa->dev, "AXI %s error\n", val ? "write" : "read");
	} else if (!(val & VDOAIST_EOT)) {
		dev_warn(vdoa->dev, "Spurious interrupt\n");
	}
	curr_ctx->completed_job++;
	complete(&curr_ctx->completion);

	return IRQ_HANDLED;
}