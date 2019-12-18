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
struct pm8001_hba_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_0 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_1 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_2 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_3 ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int RB6_ACCESS_REG ; 
 int /*<<< orphan*/  RB6_MAGIC_NUMBER_RST ; 
 int SCRATCH_PAD2_FWRDY_RST ; 
 int /*<<< orphan*/  SPC_RB6_OFFSET ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ mpi_uninit_check (struct pm8001_hba_info*) ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 soft_reset_ready_check(struct pm8001_hba_info *pm8001_ha)
{
	u32 regVal, regVal1, regVal2;
	if (mpi_uninit_check(pm8001_ha) != 0) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("MPI state is not ready\n"));
		return -1;
	}
	/* read the scratch pad 2 register bit 2 */
	regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2)
		& SCRATCH_PAD2_FWRDY_RST;
	if (regVal == SCRATCH_PAD2_FWRDY_RST) {
		PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("Firmware is ready for reset .\n"));
	} else {
		unsigned long flags;
		/* Trigger NMI twice via RB6 */
		spin_lock_irqsave(&pm8001_ha->lock, flags);
		if (-1 == pm8001_bar4_shift(pm8001_ha, RB6_ACCESS_REG)) {
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("Shift Bar4 to 0x%x failed\n",
					RB6_ACCESS_REG));
			return -1;
		}
		pm8001_cw32(pm8001_ha, 2, SPC_RB6_OFFSET,
			RB6_MAGIC_NUMBER_RST);
		pm8001_cw32(pm8001_ha, 2, SPC_RB6_OFFSET, RB6_MAGIC_NUMBER_RST);
		/* wait for 100 ms */
		mdelay(100);
		regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2) &
			SCRATCH_PAD2_FWRDY_RST;
		if (regVal != SCRATCH_PAD2_FWRDY_RST) {
			regVal1 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
			regVal2 = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("TIMEOUT:MSGU_SCRATCH_PAD1"
				"=0x%x, MSGU_SCRATCH_PAD2=0x%x\n",
				regVal1, regVal2));
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD0 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_0)));
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD3 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_3)));
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			return -1;
		}
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	}
	return 0;
}