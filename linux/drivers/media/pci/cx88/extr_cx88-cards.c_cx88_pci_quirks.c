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
 int /*<<< orphan*/  CX88X_DEVCTRL ; 
 int CX88X_EN_TBFX ; 
 int CX88X_EN_VSFX ; 
 int PCIPCI_ALIMAGIK ; 
 int PCIPCI_NATOMA ; 
 int PCIPCI_TRITON ; 
 int PCIPCI_VIAETBF ; 
 int PCIPCI_VSFX ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 unsigned int UNSET ; 
 unsigned int latency ; 
 int pci_pci_problems ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int cx88_pci_quirks(const char *name, struct pci_dev *pci)
{
	unsigned int lat = UNSET;
	u8 ctrl = 0;
	u8 value;

	/* check pci quirks */
	if (pci_pci_problems & PCIPCI_TRITON) {
		pr_info("quirk: PCIPCI_TRITON -- set TBFX\n");
		ctrl |= CX88X_EN_TBFX;
	}
	if (pci_pci_problems & PCIPCI_NATOMA) {
		pr_info("quirk: PCIPCI_NATOMA -- set TBFX\n");
		ctrl |= CX88X_EN_TBFX;
	}
	if (pci_pci_problems & PCIPCI_VIAETBF) {
		pr_info("quirk: PCIPCI_VIAETBF -- set TBFX\n");
		ctrl |= CX88X_EN_TBFX;
	}
	if (pci_pci_problems & PCIPCI_VSFX) {
		pr_info("quirk: PCIPCI_VSFX -- set VSFX\n");
		ctrl |= CX88X_EN_VSFX;
	}
#ifdef PCIPCI_ALIMAGIK
	if (pci_pci_problems & PCIPCI_ALIMAGIK) {
		pr_info("quirk: PCIPCI_ALIMAGIK -- latency fixup\n");
		lat = 0x0A;
	}
#endif

	/* check insmod options */
	if (latency != UNSET)
		lat = latency;

	/* apply stuff */
	if (ctrl) {
		pci_read_config_byte(pci, CX88X_DEVCTRL, &value);
		value |= ctrl;
		pci_write_config_byte(pci, CX88X_DEVCTRL, value);
	}
	if (lat != UNSET) {
		pr_info("setting pci latency timer to %d\n", latency);
		pci_write_config_byte(pci, PCI_LATENCY_TIMER, latency);
	}
	return 0;
}