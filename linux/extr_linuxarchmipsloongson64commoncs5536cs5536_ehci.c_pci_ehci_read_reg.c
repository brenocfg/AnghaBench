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
 int CFG_PCI_CACHE_LINE_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CFG_PCI_INTERRUPT_LINE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CFG_PCI_VENDOR_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CS5536_EHCI_CLASS_CODE ; 
 int /*<<< orphan*/  CS5536_EHCI_DEVICE_ID ; 
 int CS5536_EHCI_RANGE ; 
 int /*<<< orphan*/  CS5536_EHCI_SUB_ID ; 
 int /*<<< orphan*/  CS5536_SUB_VENDOR_ID ; 
 int /*<<< orphan*/  CS5536_USB_INTR ; 
 int /*<<< orphan*/  CS5536_VENDOR_ID ; 
 int /*<<< orphan*/  GLCP_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLCP_SOFT_COM ; 
#define  PCI_BAR0_REG 141 
 int PCI_BASE_ADDRESS_SPACE_MEMORY ; 
#define  PCI_CACHE_LINE_SIZE 140 
#define  PCI_CAPABILITY_LIST 139 
 int PCI_CAPLIST_USB_POINTER ; 
#define  PCI_CARDBUS_CIS 138 
 int PCI_CARDBUS_CIS_POINTER ; 
#define  PCI_CLASS_REVISION 137 
#define  PCI_COMMAND 136 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  PCI_DEFAULT_PIN ; 
#define  PCI_EHCI_FLADJ_REG 135 
#define  PCI_EHCI_LEGSMIEN_REG 134 
#define  PCI_EHCI_LEGSMISTS_REG 133 
 int PCI_EXPANSION_ROM_BAR ; 
#define  PCI_INTERRUPT_LINE 132 
 int /*<<< orphan*/  PCI_NORMAL_HEADER_TYPE ; 
 int /*<<< orphan*/  PCI_NORMAL_LATENCY_TIMER ; 
#define  PCI_ROM_ADDRESS 131 
#define  PCI_STATUS 130 
 int PCI_STATUS_66MHZ ; 
 int PCI_STATUS_DEVSEL_MEDIUM ; 
 int PCI_STATUS_FAST_BACK ; 
 int PCI_STATUS_PARITY ; 
#define  PCI_SUBSYSTEM_VENDOR_ID 129 
#define  PCI_VENDOR_ID 128 
 int /*<<< orphan*/  SB_ERROR ; 
 int /*<<< orphan*/  SB_MSR_REG (int /*<<< orphan*/ ) ; 
 int SB_PARE_ERR_FLAG ; 
 int SOFT_BAR_EHCI_FLAG ; 
 int /*<<< orphan*/  USB_CAP ; 
 int /*<<< orphan*/  USB_EHCI ; 
 int /*<<< orphan*/  USB_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 

u32 pci_ehci_read_reg(int reg)
{
	u32 conf_data = 0;
	u32 hi, lo;

	switch (reg) {
	case PCI_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_EHCI_DEVICE_ID, CS5536_VENDOR_ID);
		break;
	case PCI_COMMAND:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		if (hi & PCI_COMMAND_MASTER)
			conf_data |= PCI_COMMAND_MASTER;
		if (hi & PCI_COMMAND_MEMORY)
			conf_data |= PCI_COMMAND_MEMORY;
		break;
	case PCI_STATUS:
		conf_data |= PCI_STATUS_66MHZ;
		conf_data |= PCI_STATUS_FAST_BACK;
		_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
		if (lo & SB_PARE_ERR_FLAG)
			conf_data |= PCI_STATUS_PARITY;
		conf_data |= PCI_STATUS_DEVSEL_MEDIUM;
		break;
	case PCI_CLASS_REVISION:
		_rdmsr(USB_MSR_REG(USB_CAP), &hi, &lo);
		conf_data = lo & 0x000000ff;
		conf_data |= (CS5536_EHCI_CLASS_CODE << 8);
		break;
	case PCI_CACHE_LINE_SIZE:
		conf_data =
		    CFG_PCI_CACHE_LINE_SIZE(PCI_NORMAL_HEADER_TYPE,
					    PCI_NORMAL_LATENCY_TIMER);
		break;
	case PCI_BAR0_REG:
		_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
		if (lo & SOFT_BAR_EHCI_FLAG) {
			conf_data = CS5536_EHCI_RANGE |
			    PCI_BASE_ADDRESS_SPACE_MEMORY;
			lo &= ~SOFT_BAR_EHCI_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		} else {
			_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
			conf_data = lo & 0xfffff000;
		}
		break;
	case PCI_CARDBUS_CIS:
		conf_data = PCI_CARDBUS_CIS_POINTER;
		break;
	case PCI_SUBSYSTEM_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_EHCI_SUB_ID, CS5536_SUB_VENDOR_ID);
		break;
	case PCI_ROM_ADDRESS:
		conf_data = PCI_EXPANSION_ROM_BAR;
		break;
	case PCI_CAPABILITY_LIST:
		conf_data = PCI_CAPLIST_USB_POINTER;
		break;
	case PCI_INTERRUPT_LINE:
		conf_data =
		    CFG_PCI_INTERRUPT_LINE(PCI_DEFAULT_PIN, CS5536_USB_INTR);
		break;
	case PCI_EHCI_LEGSMIEN_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		conf_data = (hi & 0x003f0000) >> 16;
		break;
	case PCI_EHCI_LEGSMISTS_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		conf_data = (hi & 0x3f000000) >> 24;
		break;
	case PCI_EHCI_FLADJ_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		conf_data = hi & 0x00003f00;
		break;
	default:
		break;
	}

	return conf_data;
}