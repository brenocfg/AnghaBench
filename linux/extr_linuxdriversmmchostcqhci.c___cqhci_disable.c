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
typedef  int /*<<< orphan*/  u32 ;
struct cqhci_host {int activated; TYPE_1__* mmc; } ;
struct TYPE_2__ {int cqe_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_CFG ; 
 int /*<<< orphan*/  CQHCI_ENABLE ; 
 int /*<<< orphan*/  cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqhci_writel (struct cqhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cqhci_disable(struct cqhci_host *cq_host)
{
	u32 cqcfg;

	cqcfg = cqhci_readl(cq_host, CQHCI_CFG);
	cqcfg &= ~CQHCI_ENABLE;
	cqhci_writel(cq_host, cqcfg, CQHCI_CFG);

	cq_host->mmc->cqe_on = false;

	cq_host->activated = false;
}