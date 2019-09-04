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
 int CS5536_UART1_INTR ; 
 int CS5536_UART2_INTR ; 
 int /*<<< orphan*/  DIVIL_MSR_REG (int /*<<< orphan*/ ) ; 
#define  PCI_BAR0_REG 139 
#define  PCI_BAR1_REG 138 
#define  PCI_BAR2_REG 137 
#define  PCI_BAR3_REG 136 
#define  PCI_BAR4_REG 135 
#define  PCI_BAR5_REG 134 
#define  PCI_CACHE_LINE_SIZE 133 
#define  PCI_COMMAND 132 
 int PCI_COMMAND_IO ; 
#define  PCI_ISA_FIXUP_REG 131 
#define  PCI_STATUS 130 
 int PCI_STATUS_DETECTED_PARITY ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int PCI_STATUS_REC_TARGET_ABORT ; 
 int PCI_STATUS_SIG_TARGET_ABORT ; 
#define  PCI_UART1_INT_REG 129 
#define  PCI_UART2_INT_REG 128 
 int /*<<< orphan*/  PIC_YSEL_HIGH ; 
 int /*<<< orphan*/  SB_CTRL ; 
 int /*<<< orphan*/  SB_ERROR ; 
 int SB_MAR_ERR_EN ; 
 int SB_MAR_ERR_FLAG ; 
 int /*<<< orphan*/  SB_MSR_REG (int /*<<< orphan*/ ) ; 
 int SB_PARE_ERR_EN ; 
 int SB_PARE_ERR_FLAG ; 
 int SB_TAR_ERR_EN ; 
 int SB_TAR_ERR_FLAG ; 
 int SB_TAS_ERR_EN ; 
 int SB_TAS_ERR_FLAG ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  divil_lbar_disable () ; 
 int /*<<< orphan*/  divil_lbar_enable () ; 
 int /*<<< orphan*/  pci_isa_write_bar (int,int) ; 

void pci_isa_write_reg(int reg, u32 value)
{
	u32 hi = 0, lo = value;
	u32 temp;

	switch (reg) {
	case PCI_COMMAND:
		if (value & PCI_COMMAND_IO)
			divil_lbar_enable();
		else
			divil_lbar_disable();
		break;
	case PCI_STATUS:
		_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
		temp = lo & 0x0000ffff;
		if ((value & PCI_STATUS_SIG_TARGET_ABORT) &&
		    (lo & SB_TAS_ERR_EN))
			temp |= SB_TAS_ERR_FLAG;

		if ((value & PCI_STATUS_REC_TARGET_ABORT) &&
		    (lo & SB_TAR_ERR_EN))
			temp |= SB_TAR_ERR_FLAG;

		if ((value & PCI_STATUS_REC_MASTER_ABORT)
		    && (lo & SB_MAR_ERR_EN))
			temp |= SB_MAR_ERR_FLAG;

		if ((value & PCI_STATUS_DETECTED_PARITY)
		    && (lo & SB_PARE_ERR_EN))
			temp |= SB_PARE_ERR_FLAG;

		lo = temp;
		_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
		break;
	case PCI_CACHE_LINE_SIZE:
		value &= 0x0000ff00;
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0xffffff00;
		hi |= (value >> 8);
		_wrmsr(SB_MSR_REG(SB_CTRL), hi, lo);
		break;
	case PCI_BAR0_REG:
		pci_isa_write_bar(0, value);
		break;
	case PCI_BAR1_REG:
		pci_isa_write_bar(1, value);
		break;
	case PCI_BAR2_REG:
		pci_isa_write_bar(2, value);
		break;
	case PCI_BAR3_REG:
		pci_isa_write_bar(3, value);
		break;
	case PCI_BAR4_REG:
		pci_isa_write_bar(4, value);
		break;
	case PCI_BAR5_REG:
		pci_isa_write_bar(5, value);
		break;
	case PCI_UART1_INT_REG:
		_rdmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), &hi, &lo);
		/* disable uart1 interrupt in PIC */
		lo &= ~(0xf << 24);
		if (value)	/* enable uart1 interrupt in PIC */
			lo |= (CS5536_UART1_INTR << 24);
		_wrmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), hi, lo);
		break;
	case PCI_UART2_INT_REG:
		_rdmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), &hi, &lo);
		/* disable uart2 interrupt in PIC */
		lo &= ~(0xf << 28);
		if (value)	/* enable uart2 interrupt in PIC */
			lo |= (CS5536_UART2_INTR << 28);
		_wrmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), hi, lo);
		break;
	case PCI_ISA_FIXUP_REG:
		if (value) {
			/* enable the TARGET ABORT/MASTER ABORT etc. */
			_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
			lo |= 0x00000063;
			_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
		}

	default:
		/* ALL OTHER PCI CONFIG SPACE HEADER IS NOT IMPLEMENTED. */
		break;
	}
}