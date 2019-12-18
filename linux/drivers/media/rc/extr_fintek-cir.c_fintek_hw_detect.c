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
typedef  int u8 ;
typedef  int u16 ;
struct fintek_dev {int hw_tx_capable; int chip_major; int chip_minor; int chip_vendor; int /*<<< orphan*/  fintek_lock; int /*<<< orphan*/  logical_dev_cir; int /*<<< orphan*/  cr_dp; int /*<<< orphan*/  cr_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_CR_CLASS ; 
#define  CLASS_RX_1TX 130 
#define  CLASS_RX_2TX 129 
#define  CLASS_RX_ONLY 128 
 int /*<<< orphan*/  CR_DATA_PORT2 ; 
 int /*<<< orphan*/  CR_INDEX_PORT2 ; 
 int /*<<< orphan*/  GCR_CHIP_ID_HI ; 
 int /*<<< orphan*/  GCR_CHIP_ID_LO ; 
 int /*<<< orphan*/  GCR_CONFIG_PORT_SEL ; 
 int /*<<< orphan*/  GCR_VENDOR_ID_HI ; 
 int /*<<< orphan*/  GCR_VENDOR_ID_LO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR_REV1 ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR_REV2 ; 
 int VENDOR_ID_FINTEK ; 
 int fintek_cir_reg_read (struct fintek_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fintek_config_mode_disable (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_config_mode_enable (struct fintek_dev*) ; 
 int fintek_cr_read (struct fintek_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fit_dbg (char*,...) ; 
 int /*<<< orphan*/  fit_pr (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fintek_hw_detect(struct fintek_dev *fintek)
{
	unsigned long flags;
	u8 chip_major, chip_minor;
	u8 vendor_major, vendor_minor;
	u8 portsel, ir_class;
	u16 vendor, chip;

	fintek_config_mode_enable(fintek);

	/* Check if we're using config port 0x4e or 0x2e */
	portsel = fintek_cr_read(fintek, GCR_CONFIG_PORT_SEL);
	if (portsel == 0xff) {
		fit_pr(KERN_INFO, "first portsel read was bunk, trying alt");
		fintek_config_mode_disable(fintek);
		fintek->cr_ip = CR_INDEX_PORT2;
		fintek->cr_dp = CR_DATA_PORT2;
		fintek_config_mode_enable(fintek);
		portsel = fintek_cr_read(fintek, GCR_CONFIG_PORT_SEL);
	}
	fit_dbg("portsel reg: 0x%02x", portsel);

	ir_class = fintek_cir_reg_read(fintek, CIR_CR_CLASS);
	fit_dbg("ir_class reg: 0x%02x", ir_class);

	switch (ir_class) {
	case CLASS_RX_2TX:
	case CLASS_RX_1TX:
		fintek->hw_tx_capable = true;
		break;
	case CLASS_RX_ONLY:
	default:
		fintek->hw_tx_capable = false;
		break;
	}

	chip_major = fintek_cr_read(fintek, GCR_CHIP_ID_HI);
	chip_minor = fintek_cr_read(fintek, GCR_CHIP_ID_LO);
	chip  = chip_major << 8 | chip_minor;

	vendor_major = fintek_cr_read(fintek, GCR_VENDOR_ID_HI);
	vendor_minor = fintek_cr_read(fintek, GCR_VENDOR_ID_LO);
	vendor = vendor_major << 8 | vendor_minor;

	if (vendor != VENDOR_ID_FINTEK)
		fit_pr(KERN_WARNING, "Unknown vendor ID: 0x%04x", vendor);
	else
		fit_dbg("Read Fintek vendor ID from chip");

	fintek_config_mode_disable(fintek);

	spin_lock_irqsave(&fintek->fintek_lock, flags);
	fintek->chip_major  = chip_major;
	fintek->chip_minor  = chip_minor;
	fintek->chip_vendor = vendor;

	/*
	 * Newer reviews of this chipset uses port 8 instead of 5
	 */
	if ((chip != 0x0408) && (chip != 0x0804))
		fintek->logical_dev_cir = LOGICAL_DEV_CIR_REV2;
	else
		fintek->logical_dev_cir = LOGICAL_DEV_CIR_REV1;

	spin_unlock_irqrestore(&fintek->fintek_lock, flags);

	return 0;
}