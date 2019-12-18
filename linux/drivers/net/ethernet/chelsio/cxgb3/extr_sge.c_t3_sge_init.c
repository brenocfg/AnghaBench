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
struct sge_params {int dummy; } ;
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {int flags; TYPE_1__ params; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CMDQ_CREDIT_TH ; 
 int /*<<< orphan*/  A_SG_CONTROL ; 
 int /*<<< orphan*/  A_SG_DRB_PRI_THRESH ; 
 int /*<<< orphan*/  A_SG_EGR_RCQ_DRB_THRSH ; 
 int /*<<< orphan*/  A_SG_HI_DRB_HI_THRSH ; 
 int /*<<< orphan*/  A_SG_HI_DRB_LO_THRSH ; 
 int /*<<< orphan*/  A_SG_LO_DRB_HI_THRSH ; 
 int /*<<< orphan*/  A_SG_LO_DRB_LO_THRSH ; 
 int /*<<< orphan*/  A_SG_OCO_BASE ; 
 int /*<<< orphan*/  A_SG_TIMER_TICK ; 
 unsigned int F_AVOIDCQOVFL ; 
 unsigned int F_BIGENDIANINGRESS ; 
 unsigned int F_CONGMODE ; 
 unsigned int F_CQCRDTCTRL ; 
 unsigned int F_DROPPKT ; 
 unsigned int F_EGRGENCTRL ; 
 unsigned int F_FATLPERREN ; 
 unsigned int F_FLMODE ; 
 unsigned int F_ISCSICOALESCING ; 
 unsigned int F_ONEINTMULTQ ; 
 unsigned int F_OPTONEINTMULTQ ; 
 unsigned int F_TNLFLMODE ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ T3_REV_C ; 
 int USING_MSI ; 
 int USING_MSIX ; 
 int V_BASE1 (int) ; 
 int V_HIRCQDRBTHRSH (int) ; 
 unsigned int V_HOSTPAGESIZE (scalar_t__) ; 
 int V_LORCQDRBTHRSH (int) ; 
 unsigned int V_PKTSHIFT (int) ; 
 int V_THRESHOLD (int) ; 
 int V_TIMEOUT (int) ; 
 unsigned int V_USERSPACESIZE (unsigned int) ; 
 int core_ticks_per_usec (struct adapter*) ; 
 unsigned int ffs (int) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t3_sge_init(struct adapter *adap, struct sge_params *p)
{
	unsigned int ctrl, ups = ffs(pci_resource_len(adap->pdev, 2) >> 12);

	ctrl = F_DROPPKT | V_PKTSHIFT(2) | F_FLMODE | F_AVOIDCQOVFL |
	    F_CQCRDTCTRL | F_CONGMODE | F_TNLFLMODE | F_FATLPERREN |
	    V_HOSTPAGESIZE(PAGE_SHIFT - 11) | F_BIGENDIANINGRESS |
	    V_USERSPACESIZE(ups ? ups - 1 : 0) | F_ISCSICOALESCING;
#if SGE_NUM_GENBITS == 1
	ctrl |= F_EGRGENCTRL;
#endif
	if (adap->params.rev > 0) {
		if (!(adap->flags & (USING_MSIX | USING_MSI)))
			ctrl |= F_ONEINTMULTQ | F_OPTONEINTMULTQ;
	}
	t3_write_reg(adap, A_SG_CONTROL, ctrl);
	t3_write_reg(adap, A_SG_EGR_RCQ_DRB_THRSH, V_HIRCQDRBTHRSH(512) |
		     V_LORCQDRBTHRSH(512));
	t3_write_reg(adap, A_SG_TIMER_TICK, core_ticks_per_usec(adap) / 10);
	t3_write_reg(adap, A_SG_CMDQ_CREDIT_TH, V_THRESHOLD(32) |
		     V_TIMEOUT(200 * core_ticks_per_usec(adap)));
	t3_write_reg(adap, A_SG_HI_DRB_HI_THRSH,
		     adap->params.rev < T3_REV_C ? 1000 : 500);
	t3_write_reg(adap, A_SG_HI_DRB_LO_THRSH, 256);
	t3_write_reg(adap, A_SG_LO_DRB_HI_THRSH, 1000);
	t3_write_reg(adap, A_SG_LO_DRB_LO_THRSH, 256);
	t3_write_reg(adap, A_SG_OCO_BASE, V_BASE1(0xfff));
	t3_write_reg(adap, A_SG_DRB_PRI_THRESH, 63 * 1024);
}