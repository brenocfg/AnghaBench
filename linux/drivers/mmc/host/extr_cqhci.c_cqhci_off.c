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
typedef  int u32 ;
struct mmc_host {int cqe_on; struct cqhci_host* cqe_private; } ;
struct cqhci_host {TYPE_1__* ops; scalar_t__ recovery_halt; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct mmc_host*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_CTL ; 
 int CQHCI_HALT ; 
 int /*<<< orphan*/  CQHCI_OFF_TIMEOUT ; 
 int cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqhci_writel (struct cqhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,int) ; 

__attribute__((used)) static void cqhci_off(struct mmc_host *mmc)
{
	struct cqhci_host *cq_host = mmc->cqe_private;
	ktime_t timeout;
	bool timed_out;
	u32 reg;

	if (!cq_host->enabled || !mmc->cqe_on || cq_host->recovery_halt)
		return;

	if (cq_host->ops->disable)
		cq_host->ops->disable(mmc, false);

	cqhci_writel(cq_host, CQHCI_HALT, CQHCI_CTL);

	timeout = ktime_add_us(ktime_get(), CQHCI_OFF_TIMEOUT);
	while (1) {
		timed_out = ktime_compare(ktime_get(), timeout) > 0;
		reg = cqhci_readl(cq_host, CQHCI_CTL);
		if ((reg & CQHCI_HALT) || timed_out)
			break;
	}

	if (timed_out)
		pr_err("%s: cqhci: CQE stuck on\n", mmc_hostname(mmc));
	else
		pr_debug("%s: cqhci: CQE off\n", mmc_hostname(mmc));

	mmc->cqe_on = false;
}