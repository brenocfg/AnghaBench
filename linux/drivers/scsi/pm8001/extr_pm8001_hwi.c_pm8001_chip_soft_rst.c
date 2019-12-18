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
 int /*<<< orphan*/  GPIO_ADDR_BASE ; 
 int /*<<< orphan*/  GPIO_GPIO_0_0UTPUT_CTL_OFFSET ; 
 int /*<<< orphan*/  GSM_ADDR_BASE ; 
 int /*<<< orphan*/  GSM_CONFIG_RESET ; 
 int GSM_CONFIG_RESET_VALUE ; 
 int /*<<< orphan*/  GSM_READ_ADDR_PARITY_CHECK ; 
 int /*<<< orphan*/  GSM_WRITE_ADDR_PARITY_CHECK ; 
 int /*<<< orphan*/  GSM_WRITE_DATA_PARITY_CHECK ; 
 int /*<<< orphan*/  MBIC_AAP1_ADDR_BASE ; 
 int /*<<< orphan*/  MBIC_IOP_ADDR_BASE ; 
 int /*<<< orphan*/  MBIC_NMI_ENABLE_VPE0_AAP1 ; 
 int /*<<< orphan*/  MBIC_NMI_ENABLE_VPE0_IOP ; 
 int /*<<< orphan*/  MSGU_HOST_SCRATCH_PAD_0 ; 
 int /*<<< orphan*/  MSGU_ODCR ; 
 int /*<<< orphan*/  MSGU_ODMR ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_0 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_1 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_2 ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_3 ; 
 int ODCR_CLEAR_ALL ; 
 int ODMR_CLEAR_ALL ; 
 int /*<<< orphan*/  PCIE_ERROR_INTERRUPT ; 
 int /*<<< orphan*/  PCIE_ERROR_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  PCIE_EVENT_INTERRUPT ; 
 int /*<<< orphan*/  PCIE_EVENT_INTERRUPT_ENABLE ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int SCRATCH_PAD1_RST ; 
 int /*<<< orphan*/  SPC_REG_RESET ; 
 int SPC_REG_RESET_BDMA_CORE ; 
 int SPC_REG_RESET_OSSP ; 
 int SPC_REG_RESET_PCS_AAP1_SS ; 
 int SPC_REG_RESET_PCS_IOP_SS ; 
 int SPC_SOFT_RESET_SIGNATURE ; 
 int /*<<< orphan*/  SPC_TOP_LEVEL_ADDR_BASE ; 
 int check_fw_ready (struct pm8001_hba_info*) ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 scalar_t__ soft_reset_ready_check (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
pm8001_chip_soft_rst(struct pm8001_hba_info *pm8001_ha)
{
	u32	regVal, toggleVal;
	u32	max_wait_count;
	u32	regVal1, regVal2, regVal3;
	u32	signature = 0x252acbcd; /* for host scratch pad0 */
	unsigned long flags;

	/* step1: Check FW is ready for soft reset */
	if (soft_reset_ready_check(pm8001_ha) != 0) {
		PM8001_FAIL_DBG(pm8001_ha, pm8001_printk("FW is not ready\n"));
		return -1;
	}

	/* step 2: clear NMI status register on AAP1 and IOP, write the same
	value to clear */
	/* map 0x60000 to BAR4(0x20), BAR2(win) */
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	if (-1 == pm8001_bar4_shift(pm8001_ha, MBIC_AAP1_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Shift Bar4 to 0x%x failed\n",
			MBIC_AAP1_ADDR_BASE));
		return -1;
	}
	regVal = pm8001_cr32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_IOP);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("MBIC - NMI Enable VPE0 (IOP)= 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_IOP, 0x0);
	/* map 0x70000 to BAR4(0x20), BAR2(win) */
	if (-1 == pm8001_bar4_shift(pm8001_ha, MBIC_IOP_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Shift Bar4 to 0x%x failed\n",
			MBIC_IOP_ADDR_BASE));
		return -1;
	}
	regVal = pm8001_cr32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_AAP1);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("MBIC - NMI Enable VPE0 (AAP1)= 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 2, MBIC_NMI_ENABLE_VPE0_AAP1, 0x0);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT_ENABLE);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("PCIE -Event Interrupt Enable = 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT_ENABLE, 0x0);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("PCIE - Event Interrupt  = 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 1, PCIE_EVENT_INTERRUPT, regVal);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT_ENABLE);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("PCIE -Error Interrupt Enable = 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT_ENABLE, 0x0);

	regVal = pm8001_cr32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("PCIE - Error Interrupt = 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 1, PCIE_ERROR_INTERRUPT, regVal);

	/* read the scratch pad 1 register bit 2 */
	regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1)
		& SCRATCH_PAD1_RST;
	toggleVal = regVal ^ SCRATCH_PAD1_RST;

	/* set signature in host scratch pad0 register to tell SPC that the
	host performs the soft reset */
	pm8001_cw32(pm8001_ha, 0, MSGU_HOST_SCRATCH_PAD_0, signature);

	/* read required registers for confirmming */
	/* map 0x0700000 to BAR4(0x20), BAR2(win) */
	if (-1 == pm8001_bar4_shift(pm8001_ha, GSM_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Shift Bar4 to 0x%x failed\n",
			GSM_ADDR_BASE));
		return -1;
	}
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x0(0x00007b88)-GSM Configuration and"
		" Reset = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET)));

	/* step 3: host read GSM Configuration and Reset register */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET);
	/* Put those bits to low */
	/* GSM XCBI offset = 0x70 0000
	0x00 Bit 13 COM_SLV_SW_RSTB 1
	0x00 Bit 12 QSSP_SW_RSTB 1
	0x00 Bit 11 RAAE_SW_RSTB 1
	0x00 Bit 9 RB_1_SW_RSTB 1
	0x00 Bit 8 SM_SW_RSTB 1
	*/
	regVal &= ~(0x00003b00);
	/* host write GSM Configuration and Reset register */
	pm8001_cw32(pm8001_ha, 2, GSM_CONFIG_RESET, regVal);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x0 (0x00007b88 ==> 0x00004088) - GSM "
		"Configuration and Reset is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET)));

	/* step 4: */
	/* disable GSM - Read Address Parity Check */
	regVal1 = pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700038 - Read Address Parity Check "
		"Enable = 0x%x\n", regVal1));
	pm8001_cw32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK, 0x0);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700038 - Read Address Parity Check Enable"
		"is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK)));

	/* disable GSM - Write Address Parity Check */
	regVal2 = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700040 - Write Address Parity Check"
		" Enable = 0x%x\n", regVal2));
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK, 0x0);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700040 - Write Address Parity Check "
		"Enable is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK)));

	/* disable GSM - Write Data Parity Check */
	regVal3 = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x300048 - Write Data Parity Check"
		" Enable = 0x%x\n", regVal3));
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK, 0x0);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x300048 - Write Data Parity Check Enable"
		"is set to = 0x%x\n",
	pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK)));

	/* step 5: delay 10 usec */
	udelay(10);
	/* step 5-b: set GPIO-0 output control to tristate anyway */
	if (-1 == pm8001_bar4_shift(pm8001_ha, GPIO_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_INIT_DBG(pm8001_ha,
				pm8001_printk("Shift Bar4 to 0x%x failed\n",
				GPIO_ADDR_BASE));
		return -1;
	}
	regVal = pm8001_cr32(pm8001_ha, 2, GPIO_GPIO_0_0UTPUT_CTL_OFFSET);
	PM8001_INIT_DBG(pm8001_ha,
			pm8001_printk("GPIO Output Control Register:"
			" = 0x%x\n", regVal));
	/* set GPIO-0 output control to tri-state */
	regVal &= 0xFFFFFFFC;
	pm8001_cw32(pm8001_ha, 2, GPIO_GPIO_0_0UTPUT_CTL_OFFSET, regVal);

	/* Step 6: Reset the IOP and AAP1 */
	/* map 0x00000 to BAR4(0x20), BAR2(win) */
	if (-1 == pm8001_bar4_shift(pm8001_ha, SPC_TOP_LEVEL_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("SPC Shift Bar4 to 0x%x failed\n",
			SPC_TOP_LEVEL_ADDR_BASE));
		return -1;
	}
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("Top Register before resetting IOP/AAP1"
		":= 0x%x\n", regVal));
	regVal &= ~(SPC_REG_RESET_PCS_IOP_SS | SPC_REG_RESET_PCS_AAP1_SS);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 7: Reset the BDMA/OSSP */
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("Top Register before resetting BDMA/OSSP"
		": = 0x%x\n", regVal));
	regVal &= ~(SPC_REG_RESET_BDMA_CORE | SPC_REG_RESET_OSSP);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 8: delay 10 usec */
	udelay(10);

	/* step 9: bring the BDMA and OSSP out of reset */
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("Top Register before bringing up BDMA/OSSP"
		":= 0x%x\n", regVal));
	regVal |= (SPC_REG_RESET_BDMA_CORE | SPC_REG_RESET_OSSP);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 10: delay 10 usec */
	udelay(10);

	/* step 11: reads and sets the GSM Configuration and Reset Register */
	/* map 0x0700000 to BAR4(0x20), BAR2(win) */
	if (-1 == pm8001_bar4_shift(pm8001_ha, GSM_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("SPC Shift Bar4 to 0x%x failed\n",
			GSM_ADDR_BASE));
		return -1;
	}
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x0 (0x00007b88)-GSM Configuration and "
		"Reset = 0x%x\n", pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET)));
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET);
	/* Put those bits to high */
	/* GSM XCBI offset = 0x70 0000
	0x00 Bit 13 COM_SLV_SW_RSTB 1
	0x00 Bit 12 QSSP_SW_RSTB 1
	0x00 Bit 11 RAAE_SW_RSTB 1
	0x00 Bit 9   RB_1_SW_RSTB 1
	0x00 Bit 8   SM_SW_RSTB 1
	*/
	regVal |= (GSM_CONFIG_RESET_VALUE);
	pm8001_cw32(pm8001_ha, 2, GSM_CONFIG_RESET, regVal);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM (0x00004088 ==> 0x00007b88) - GSM"
		" Configuration and Reset is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_CONFIG_RESET)));

	/* step 12: Restore GSM - Read Address Parity Check */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK);
	/* just for debugging */
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700038 - Read Address Parity Check Enable"
		" = 0x%x\n", regVal));
	pm8001_cw32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK, regVal1);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700038 - Read Address Parity"
		" Check Enable is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_READ_ADDR_PARITY_CHECK)));
	/* Restore GSM - Write Address Parity Check */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK);
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK, regVal2);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700040 - Write Address Parity Check"
		" Enable is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_WRITE_ADDR_PARITY_CHECK)));
	/* Restore GSM - Write Data Parity Check */
	regVal = pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK);
	pm8001_cw32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK, regVal3);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("GSM 0x700048 - Write Data Parity Check Enable"
		"is set to = 0x%x\n",
		pm8001_cr32(pm8001_ha, 2, GSM_WRITE_DATA_PARITY_CHECK)));

	/* step 13: bring the IOP and AAP1 out of reset */
	/* map 0x00000 to BAR4(0x20), BAR2(win) */
	if (-1 == pm8001_bar4_shift(pm8001_ha, SPC_TOP_LEVEL_ADDR_BASE)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Shift Bar4 to 0x%x failed\n",
			SPC_TOP_LEVEL_ADDR_BASE));
		return -1;
	}
	regVal = pm8001_cr32(pm8001_ha, 2, SPC_REG_RESET);
	regVal |= (SPC_REG_RESET_PCS_IOP_SS | SPC_REG_RESET_PCS_AAP1_SS);
	pm8001_cw32(pm8001_ha, 2, SPC_REG_RESET, regVal);

	/* step 14: delay 10 usec - Normal Mode */
	udelay(10);
	/* check Soft Reset Normal mode or Soft Reset HDA mode */
	if (signature == SPC_SOFT_RESET_SIGNATURE) {
		/* step 15 (Normal Mode): wait until scratch pad1 register
		bit 2 toggled */
		max_wait_count = 2 * 1000 * 1000;/* 2 sec */
		do {
			udelay(1);
			regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1) &
				SCRATCH_PAD1_RST;
		} while ((regVal != toggleVal) && (--max_wait_count));

		if (!max_wait_count) {
			regVal = pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_1);
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("TIMEOUT : ToggleVal 0x%x,"
				"MSGU_SCRATCH_PAD1 = 0x%x\n",
				toggleVal, regVal));
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD0 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_0)));
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD2 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_2)));
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD3 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_3)));
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			return -1;
		}

		/* step 16 (Normal) - Clear ODMR and ODCR */
		pm8001_cw32(pm8001_ha, 0, MSGU_ODCR, ODCR_CLEAR_ALL);
		pm8001_cw32(pm8001_ha, 0, MSGU_ODMR, ODMR_CLEAR_ALL);

		/* step 17 (Normal Mode): wait for the FW and IOP to get
		ready - 1 sec timeout */
		/* Wait for the SPC Configuration Table to be ready */
		if (check_fw_ready(pm8001_ha) == -1) {
			regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1);
			/* return error if MPI Configuration Table not ready */
			PM8001_INIT_DBG(pm8001_ha,
				pm8001_printk("FW not ready SCRATCH_PAD1"
				" = 0x%x\n", regVal));
			regVal = pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_2);
			/* return error if MPI Configuration Table not ready */
			PM8001_INIT_DBG(pm8001_ha,
				pm8001_printk("FW not ready SCRATCH_PAD2"
				" = 0x%x\n", regVal));
			PM8001_INIT_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD0 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_0)));
			PM8001_INIT_DBG(pm8001_ha,
				pm8001_printk("SCRATCH_PAD3 value = 0x%x\n",
				pm8001_cr32(pm8001_ha, 0,
				MSGU_SCRATCH_PAD_3)));
			spin_unlock_irqrestore(&pm8001_ha->lock, flags);
			return -1;
		}
	}
	pm8001_bar4_shift(pm8001_ha, 0);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);

	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("SPC soft reset Complete\n"));
	return 0;
}