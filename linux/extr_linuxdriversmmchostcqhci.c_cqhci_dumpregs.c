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
struct mmc_host {int dummy; } ;
struct cqhci_host {TYPE_1__* ops; struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dumpregs ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_CAP ; 
 int /*<<< orphan*/  CQHCI_CFG ; 
 int /*<<< orphan*/  CQHCI_CRA ; 
 int /*<<< orphan*/  CQHCI_CRDCT ; 
 int /*<<< orphan*/  CQHCI_CRI ; 
 int /*<<< orphan*/  CQHCI_CTL ; 
 int /*<<< orphan*/  CQHCI_DPT ; 
 int /*<<< orphan*/  CQHCI_DQS ; 
 int /*<<< orphan*/  CQHCI_DUMP (char*,...) ; 
 int /*<<< orphan*/  CQHCI_IC ; 
 int /*<<< orphan*/  CQHCI_IS ; 
 int /*<<< orphan*/  CQHCI_ISGE ; 
 int /*<<< orphan*/  CQHCI_ISTE ; 
 int /*<<< orphan*/  CQHCI_RMEM ; 
 int /*<<< orphan*/  CQHCI_SSC1 ; 
 int /*<<< orphan*/  CQHCI_SSC2 ; 
 int /*<<< orphan*/  CQHCI_TCLR ; 
 int /*<<< orphan*/  CQHCI_TCN ; 
 int /*<<< orphan*/  CQHCI_TDBR ; 
 int /*<<< orphan*/  CQHCI_TDLBA ; 
 int /*<<< orphan*/  CQHCI_TDLBAU ; 
 int /*<<< orphan*/  CQHCI_TERRI ; 
 int /*<<< orphan*/  CQHCI_VER ; 
 int /*<<< orphan*/  cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

__attribute__((used)) static void cqhci_dumpregs(struct cqhci_host *cq_host)
{
	struct mmc_host *mmc = cq_host->mmc;

	CQHCI_DUMP("============ CQHCI REGISTER DUMP ===========\n");

	CQHCI_DUMP("Caps:      0x%08x | Version:  0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_CAP),
		   cqhci_readl(cq_host, CQHCI_VER));
	CQHCI_DUMP("Config:    0x%08x | Control:  0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_CFG),
		   cqhci_readl(cq_host, CQHCI_CTL));
	CQHCI_DUMP("Int stat:  0x%08x | Int enab: 0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_IS),
		   cqhci_readl(cq_host, CQHCI_ISTE));
	CQHCI_DUMP("Int sig:   0x%08x | Int Coal: 0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_ISGE),
		   cqhci_readl(cq_host, CQHCI_IC));
	CQHCI_DUMP("TDL base:  0x%08x | TDL up32: 0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_TDLBA),
		   cqhci_readl(cq_host, CQHCI_TDLBAU));
	CQHCI_DUMP("Doorbell:  0x%08x | TCN:      0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_TDBR),
		   cqhci_readl(cq_host, CQHCI_TCN));
	CQHCI_DUMP("Dev queue: 0x%08x | Dev Pend: 0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_DQS),
		   cqhci_readl(cq_host, CQHCI_DPT));
	CQHCI_DUMP("Task clr:  0x%08x | SSC1:     0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_TCLR),
		   cqhci_readl(cq_host, CQHCI_SSC1));
	CQHCI_DUMP("SSC2:      0x%08x | DCMD rsp: 0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_SSC2),
		   cqhci_readl(cq_host, CQHCI_CRDCT));
	CQHCI_DUMP("RED mask:  0x%08x | TERRI:    0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_RMEM),
		   cqhci_readl(cq_host, CQHCI_TERRI));
	CQHCI_DUMP("Resp idx:  0x%08x | Resp arg: 0x%08x\n",
		   cqhci_readl(cq_host, CQHCI_CRI),
		   cqhci_readl(cq_host, CQHCI_CRA));

	if (cq_host->ops->dumpregs)
		cq_host->ops->dumpregs(mmc);
	else
		CQHCI_DUMP(": ===========================================\n");
}