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
typedef  int u8 ;
struct at86rf230_state_change {int* buf; struct at86rf230_local* lp; } ;
struct at86rf230_local {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int IRQ_TRX_END ; 
 int /*<<< orphan*/  at86rf230_irq_trx_end (struct at86rf230_state_change*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct at86rf230_state_change*) ; 

__attribute__((used)) static void
at86rf230_irq_status(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;
	const u8 *buf = ctx->buf;
	u8 irq = buf[1];

	enable_irq(lp->spi->irq);

	if (irq & IRQ_TRX_END) {
		at86rf230_irq_trx_end(ctx);
	} else {
		dev_err(&lp->spi->dev, "not supported irq %02x received\n",
			irq);
		kfree(ctx);
	}
}