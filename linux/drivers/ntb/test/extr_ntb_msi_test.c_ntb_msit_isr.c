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
struct ntb_msit_isr_ctx {int /*<<< orphan*/  occurrences; int /*<<< orphan*/  irq_idx; struct ntb_msit_ctx* nm; } ;
struct ntb_msit_ctx {TYPE_1__* ntb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ntb_msit_isr(int irq, void *dev)
{
	struct ntb_msit_isr_ctx *isr_ctx = dev;
	struct ntb_msit_ctx *nm = isr_ctx->nm;

	dev_dbg(&nm->ntb->dev, "Interrupt Occurred: %d",
		isr_ctx->irq_idx);

	isr_ctx->occurrences++;

	return IRQ_HANDLED;
}