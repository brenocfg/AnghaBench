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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ssb_bus {int sprom_size; scalar_t__ sprom_offset; scalar_t__ mmio; struct pci_dev* host_pci; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_SPROMCTL ; 
 int /*<<< orphan*/  SSB_SPROMCTL_WE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  writew (int const,scalar_t__) ; 

__attribute__((used)) static int sprom_do_write(struct ssb_bus *bus, const u16 *sprom)
{
	struct pci_dev *pdev = bus->host_pci;
	int i, err;
	u32 spromctl;
	u16 size = bus->sprom_size;

	pr_notice("Writing SPROM. Do NOT turn off the power! Please stand by...\n");
	err = pci_read_config_dword(pdev, SSB_SPROMCTL, &spromctl);
	if (err)
		goto err_ctlreg;
	spromctl |= SSB_SPROMCTL_WE;
	err = pci_write_config_dword(pdev, SSB_SPROMCTL, spromctl);
	if (err)
		goto err_ctlreg;
	pr_notice("[ 0%%");
	msleep(500);
	for (i = 0; i < size; i++) {
		if (i == size / 4)
			pr_cont("25%%");
		else if (i == size / 2)
			pr_cont("50%%");
		else if (i == (size * 3) / 4)
			pr_cont("75%%");
		else if (i % 2)
			pr_cont(".");
		writew(sprom[i], bus->mmio + bus->sprom_offset + (i * 2));
		msleep(20);
	}
	err = pci_read_config_dword(pdev, SSB_SPROMCTL, &spromctl);
	if (err)
		goto err_ctlreg;
	spromctl &= ~SSB_SPROMCTL_WE;
	err = pci_write_config_dword(pdev, SSB_SPROMCTL, spromctl);
	if (err)
		goto err_ctlreg;
	msleep(500);
	pr_cont("100%% ]\n");
	pr_notice("SPROM written\n");

	return 0;
err_ctlreg:
	pr_err("Could not access SPROM control register.\n");
	return err;
}