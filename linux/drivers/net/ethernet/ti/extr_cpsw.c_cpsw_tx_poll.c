#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct napi_struct {int dummy; } ;
struct cpsw_common {int tx_irq_disabled; int /*<<< orphan*/ * irqs_table; TYPE_2__* wr_regs; TYPE_1__* txv; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_en; } ;
struct TYPE_3__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int cpdma_chan_process (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct cpsw_common* napi_to_cpsw (struct napi_struct*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpsw_tx_poll(struct napi_struct *napi_tx, int budget)
{
	struct cpsw_common *cpsw = napi_to_cpsw(napi_tx);
	int num_tx;

	num_tx = cpdma_chan_process(cpsw->txv[0].ch, budget);
	if (num_tx < budget) {
		napi_complete(napi_tx);
		writel(0xff, &cpsw->wr_regs->tx_en);
		if (cpsw->tx_irq_disabled) {
			cpsw->tx_irq_disabled = false;
			enable_irq(cpsw->irqs_table[1]);
		}
	}

	return num_tx;
}