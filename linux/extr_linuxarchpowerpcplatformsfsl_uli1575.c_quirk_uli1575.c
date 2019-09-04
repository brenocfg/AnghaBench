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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ULI_8259_IRQ11 ; 
 int ULI_8259_IRQ14 ; 
 int ULI_8259_IRQ15 ; 
 int ULI_PIRQA ; 
 int ULI_PIRQB ; 
 int ULI_PIRQD ; 
 int ULI_PIRQE ; 
 int ULI_PIRQF ; 
 int ULI_PIRQG ; 
 int /*<<< orphan*/  is_quirk_valid () ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 
 int* uli_pirq_to_irq ; 

__attribute__((used)) static void quirk_uli1575(struct pci_dev *dev)
{
	int i;

	if (!is_quirk_valid())
		return;

	/*
	 * ULI1575 interrupts route setup
	 */

	/* ULI1575 IRQ mapping conf register maps PIRQx to IRQn */
	for (i = 0; i < 4; i++) {
		u8 val = uli_pirq_to_irq[i*2] | (uli_pirq_to_irq[i*2+1] << 4);
		pci_write_config_byte(dev, 0x48 + i, val);
	}

	/* USB 1.1 OHCI controller 1: dev 28, func 0 - IRQ12 */
	pci_write_config_byte(dev, 0x86, ULI_PIRQD);

	/* USB 1.1 OHCI controller 2: dev 28, func 1 - IRQ9 */
	pci_write_config_byte(dev, 0x87, ULI_PIRQA);

	/* USB 1.1 OHCI controller 3: dev 28, func 2 - IRQ10 */
	pci_write_config_byte(dev, 0x88, ULI_PIRQB);

	/* Lan controller: dev 27, func 0 - IRQ6 */
	pci_write_config_byte(dev, 0x89, ULI_PIRQF);

	/* AC97 Audio controller: dev 29, func 0 - IRQ6 */
	pci_write_config_byte(dev, 0x8a, ULI_PIRQF);

	/* Modem controller: dev 29, func 1 - IRQ6 */
	pci_write_config_byte(dev, 0x8b, ULI_PIRQF);

	/* HD Audio controller: dev 29, func 2 - IRQ6 */
	pci_write_config_byte(dev, 0x8c, ULI_PIRQF);

	/* SATA controller: dev 31, func 1 - IRQ5 */
	pci_write_config_byte(dev, 0x8d, ULI_PIRQE);

	/* SMB interrupt: dev 30, func 1 - IRQ7 */
	pci_write_config_byte(dev, 0x8e, ULI_PIRQG);

	/* PMU ACPI SCI interrupt: dev 30, func 2 - IRQ7 */
	pci_write_config_byte(dev, 0x8f, ULI_PIRQG);

	/* USB 2.0 controller: dev 28, func 3 */
	pci_write_config_byte(dev, 0x74, ULI_8259_IRQ11);

	/* Primary PATA IDE IRQ: 14
	 * Secondary PATA IDE IRQ: 15
	 */
	pci_write_config_byte(dev, 0x44, 0x30 | ULI_8259_IRQ14);
	pci_write_config_byte(dev, 0x75, ULI_8259_IRQ15);
}