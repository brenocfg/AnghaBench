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
struct resource {int dummy; } ;
struct pci_ecam_ops {int dummy; } ;
struct acpi_pci_root {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void pci_mcfg_apply_quirks(struct acpi_pci_root *root,
				  struct resource *cfgres,
				  struct pci_ecam_ops **ecam_ops)
{
#ifdef CONFIG_PCI_QUIRKS
	u16 segment = root->segment;
	struct resource *bus_range = &root->secondary;
	struct mcfg_fixup *f;
	int i;

	for (i = 0, f = mcfg_quirks; i < ARRAY_SIZE(mcfg_quirks); i++, f++) {
		if (pci_mcfg_quirk_matches(f, segment, bus_range)) {
			if (f->cfgres.start)
				*cfgres = f->cfgres;
			if (f->ops)
				*ecam_ops =  f->ops;
			dev_info(&root->device->dev, "MCFG quirk: ECAM at %pR for %pR with %ps\n",
				 cfgres, bus_range, *ecam_ops);
			return;
		}
	}
#endif
}