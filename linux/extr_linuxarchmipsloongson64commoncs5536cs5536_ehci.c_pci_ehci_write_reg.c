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
 int /*<<< orphan*/  GLCP_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLCP_SOFT_COM ; 
 int /*<<< orphan*/  GLIU_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLIU_P2D_BM4 ; 
#define  PCI_BAR0_REG 132 
 int PCI_BAR_RANGE_MASK ; 
#define  PCI_COMMAND 131 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
#define  PCI_EHCI_FLADJ_REG 130 
#define  PCI_EHCI_LEGSMIEN_REG 129 
#define  PCI_STATUS 128 
 int PCI_STATUS_PARITY ; 
 int /*<<< orphan*/  SB_ERROR ; 
 int /*<<< orphan*/  SB_MSR_REG (int /*<<< orphan*/ ) ; 
 int SB_PARE_ERR_FLAG ; 
 int SOFT_BAR_EHCI_FLAG ; 
 int /*<<< orphan*/  USB_EHCI ; 
 int /*<<< orphan*/  USB_MSR_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 

void pci_ehci_write_reg(int reg, u32 value)
{
	u32 hi = 0, lo = value;

	switch (reg) {
	case PCI_COMMAND:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		if (value & PCI_COMMAND_MASTER)
			hi |= PCI_COMMAND_MASTER;
		else
			hi &= ~PCI_COMMAND_MASTER;

		if (value & PCI_COMMAND_MEMORY)
			hi |= PCI_COMMAND_MEMORY;
		else
			hi &= ~PCI_COMMAND_MEMORY;
		_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);
		break;
	case PCI_STATUS:
		if (value & PCI_STATUS_PARITY) {
			_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
			if (lo & SB_PARE_ERR_FLAG) {
				lo = (lo & 0x0000ffff) | SB_PARE_ERR_FLAG;
				_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
			}
		}
		break;
	case PCI_BAR0_REG:
		if (value == PCI_BAR_RANGE_MASK) {
			_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
			lo |= SOFT_BAR_EHCI_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		} else if ((value & 0x01) == 0x00) {
			_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
			lo = value;
			_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);

			value &= 0xfffffff0;
			hi = 0x40000000 | ((value & 0xff000000) >> 24);
			lo = 0x000fffff | ((value & 0x00fff000) << 8);
			_wrmsr(GLIU_MSR_REG(GLIU_P2D_BM4), hi, lo);
		}
		break;
	case PCI_EHCI_LEGSMIEN_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		hi &= 0x003f0000;
		hi |= (value & 0x3f) << 16;
		_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);
		break;
	case PCI_EHCI_FLADJ_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		hi &= ~0x00003f00;
		hi |= value & 0x00003f00;
		_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);
		break;
	default:
		break;
	}
}