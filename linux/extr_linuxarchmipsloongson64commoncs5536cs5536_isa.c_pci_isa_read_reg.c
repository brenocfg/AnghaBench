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

/* Variables and functions */
 int CFG_PCI_CACHE_LINE_SIZE (int /*<<< orphan*/ ,int) ; 
 int CFG_PCI_INTERRUPT_LINE (int,int) ; 
 int CFG_PCI_VENDOR_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CS5536_ISA_CLASS_CODE ; 
 int /*<<< orphan*/  CS5536_ISA_DEVICE_ID ; 
 int /*<<< orphan*/  CS5536_ISA_SUB_ID ; 
 int /*<<< orphan*/  CS5536_SUB_VENDOR_ID ; 
 int /*<<< orphan*/  CS5536_VENDOR_ID ; 
 int /*<<< orphan*/  DIVIL_LBAR_SMB ; 
 int /*<<< orphan*/  DIVIL_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLCP_CHIP_REV_ID ; 
 int /*<<< orphan*/  GLCP_MSR_REG (int /*<<< orphan*/ ) ; 
#define  PCI_BAR0_REG 143 
#define  PCI_BAR1_REG 142 
#define  PCI_BAR2_REG 141 
#define  PCI_BAR3_REG 140 
#define  PCI_BAR4_REG 139 
#define  PCI_BAR5_REG 138 
 int /*<<< orphan*/  PCI_BRIDGE_HEADER_TYPE ; 
#define  PCI_CACHE_LINE_SIZE 137 
#define  PCI_CAPABILITY_LIST 136 
 int PCI_CAPLIST_POINTER ; 
#define  PCI_CARDBUS_CIS 135 
 int PCI_CARDBUS_CIS_POINTER ; 
#define  PCI_CLASS_REVISION 134 
#define  PCI_COMMAND 133 
 int PCI_COMMAND_IO ; 
 int PCI_EXPANSION_ROM_BAR ; 
#define  PCI_INTERRUPT_LINE 132 
#define  PCI_ROM_ADDRESS 131 
#define  PCI_STATUS 130 
 int PCI_STATUS_66MHZ ; 
 int PCI_STATUS_DETECTED_PARITY ; 
 int PCI_STATUS_DEVSEL_MEDIUM ; 
 int PCI_STATUS_FAST_BACK ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int PCI_STATUS_REC_TARGET_ABORT ; 
 int PCI_STATUS_SIG_TARGET_ABORT ; 
#define  PCI_SUBSYSTEM_VENDOR_ID 129 
#define  PCI_VENDOR_ID 128 
 int /*<<< orphan*/  SB_CTRL ; 
 int /*<<< orphan*/  SB_ERROR ; 
 int SB_MAR_ERR_FLAG ; 
 int /*<<< orphan*/  SB_MSR_REG (int /*<<< orphan*/ ) ; 
 int SB_PARE_ERR_FLAG ; 
 int SB_TAR_ERR_FLAG ; 
 int SB_TAS_ERR_FLAG ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int pci_isa_read_bar (int) ; 

u32 pci_isa_read_reg(int reg)
{
	u32 conf_data = 0;
	u32 hi, lo;

	switch (reg) {
	case PCI_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_ISA_DEVICE_ID, CS5536_VENDOR_ID);
		break;
	case PCI_COMMAND:
		/* we just check the first LBAR for the IO enable bit, */
		/* maybe we should changed later. */
		_rdmsr(DIVIL_MSR_REG(DIVIL_LBAR_SMB), &hi, &lo);
		if (hi & 0x01)
			conf_data |= PCI_COMMAND_IO;
		break;
	case PCI_STATUS:
		conf_data |= PCI_STATUS_66MHZ;
		conf_data |= PCI_STATUS_DEVSEL_MEDIUM;
		conf_data |= PCI_STATUS_FAST_BACK;

		_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
		if (lo & SB_TAS_ERR_FLAG)
			conf_data |= PCI_STATUS_SIG_TARGET_ABORT;
		if (lo & SB_TAR_ERR_FLAG)
			conf_data |= PCI_STATUS_REC_TARGET_ABORT;
		if (lo & SB_MAR_ERR_FLAG)
			conf_data |= PCI_STATUS_REC_MASTER_ABORT;
		if (lo & SB_PARE_ERR_FLAG)
			conf_data |= PCI_STATUS_DETECTED_PARITY;
		break;
	case PCI_CLASS_REVISION:
		_rdmsr(GLCP_MSR_REG(GLCP_CHIP_REV_ID), &hi, &lo);
		conf_data = lo & 0x000000ff;
		conf_data |= (CS5536_ISA_CLASS_CODE << 8);
		break;
	case PCI_CACHE_LINE_SIZE:
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0x000000f8;
		conf_data = CFG_PCI_CACHE_LINE_SIZE(PCI_BRIDGE_HEADER_TYPE, hi);
		break;
		/*
		 * we only use the LBAR of DIVIL, no RCONF used.
		 * all of them are IO space.
		 */
	case PCI_BAR0_REG:
		return pci_isa_read_bar(0);
		break;
	case PCI_BAR1_REG:
		return pci_isa_read_bar(1);
		break;
	case PCI_BAR2_REG:
		return pci_isa_read_bar(2);
		break;
	case PCI_BAR3_REG:
		break;
	case PCI_BAR4_REG:
		return pci_isa_read_bar(4);
		break;
	case PCI_BAR5_REG:
		return pci_isa_read_bar(5);
		break;
	case PCI_CARDBUS_CIS:
		conf_data = PCI_CARDBUS_CIS_POINTER;
		break;
	case PCI_SUBSYSTEM_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_ISA_SUB_ID, CS5536_SUB_VENDOR_ID);
		break;
	case PCI_ROM_ADDRESS:
		conf_data = PCI_EXPANSION_ROM_BAR;
		break;
	case PCI_CAPABILITY_LIST:
		conf_data = PCI_CAPLIST_POINTER;
		break;
	case PCI_INTERRUPT_LINE:
		/* no interrupt used here */
		conf_data = CFG_PCI_INTERRUPT_LINE(0x00, 0x00);
		break;
	default:
		break;
	}

	return conf_data;
}