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
struct notifier_block {int dummy; } ;
struct altr_stratix10_edac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_MC ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int NOTIFY_DONE ; 
 int S10_DDR0_IRQ_MASK ; 
 int /*<<< orphan*/  S10_DERRADDR_OFST ; 
 int /*<<< orphan*/  S10_SYSMGR_ECC_INTSTAT_DERR_OFST ; 
 int /*<<< orphan*/  S10_SYSMGR_UE_ADDR_OFST ; 
 int /*<<< orphan*/  S10_SYSMGR_UE_VAL_OFST ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  panic_notifier ; 
 int /*<<< orphan*/  s10_protected_reg_read (struct altr_stratix10_edac*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  s10_protected_reg_write (struct altr_stratix10_edac*,int /*<<< orphan*/ ,int) ; 
 struct altr_stratix10_edac* to_s10edac (struct notifier_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s10_edac_dberr_handler(struct notifier_block *this,
				  unsigned long event, void *ptr)
{
	struct altr_stratix10_edac *edac = to_s10edac(this, panic_notifier);
	int err_addr, dberror;

	s10_protected_reg_read(edac, S10_SYSMGR_ECC_INTSTAT_DERR_OFST,
			       &dberror);
	/* Remember the UE Errors for a reboot */
	s10_protected_reg_write(edac, S10_SYSMGR_UE_VAL_OFST, dberror);
	if (dberror & S10_DDR0_IRQ_MASK) {
		s10_protected_reg_read(edac, S10_DERRADDR_OFST, &err_addr);
		/* Remember the UE Error address */
		s10_protected_reg_write(edac, S10_SYSMGR_UE_ADDR_OFST,
					err_addr);
		edac_printk(KERN_ERR, EDAC_MC,
			    "EDAC: [Uncorrectable errors @ 0x%08X]\n\n",
			    err_addr);
	}

	return NOTIFY_DONE;
}