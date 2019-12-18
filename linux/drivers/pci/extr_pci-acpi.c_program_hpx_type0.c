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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int class; } ;
struct hpx_type0 {int revision; scalar_t__ enable_perr; int /*<<< orphan*/  latency_timer; scalar_t__ enable_serr; int /*<<< orphan*/  cache_line_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int /*<<< orphan*/  PCI_BRIDGE_CTL_PARITY ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_PARITY ; 
 int /*<<< orphan*/  PCI_COMMAND_SERR ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  PCI_SEC_LATENCY_TIMER ; 
 struct hpx_type0 pci_default_type0 ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_hpx_type0(struct pci_dev *dev, struct hpx_type0 *hpx)
{
	u16 pci_cmd, pci_bctl;

	if (!hpx)
		hpx = &pci_default_type0;

	if (hpx->revision > 1) {
		pci_warn(dev, "PCI settings rev %d not supported; using defaults\n",
			 hpx->revision);
		hpx = &pci_default_type0;
	}

	pci_write_config_byte(dev, PCI_CACHE_LINE_SIZE, hpx->cache_line_size);
	pci_write_config_byte(dev, PCI_LATENCY_TIMER, hpx->latency_timer);
	pci_read_config_word(dev, PCI_COMMAND, &pci_cmd);
	if (hpx->enable_serr)
		pci_cmd |= PCI_COMMAND_SERR;
	if (hpx->enable_perr)
		pci_cmd |= PCI_COMMAND_PARITY;
	pci_write_config_word(dev, PCI_COMMAND, pci_cmd);

	/* Program bridge control value */
	if ((dev->class >> 8) == PCI_CLASS_BRIDGE_PCI) {
		pci_write_config_byte(dev, PCI_SEC_LATENCY_TIMER,
				      hpx->latency_timer);
		pci_read_config_word(dev, PCI_BRIDGE_CONTROL, &pci_bctl);
		if (hpx->enable_perr)
			pci_bctl |= PCI_BRIDGE_CTL_PARITY;
		pci_write_config_word(dev, PCI_BRIDGE_CONTROL, pci_bctl);
	}
}