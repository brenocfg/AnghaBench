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
struct pci_epf_test_reg {int dummy; } ;
struct pci_epf_test {int test_reg_bar; void** reg; struct pci_epc_features* epc_features; } ;
struct pci_epf_bar {int flags; } ;
struct device {int dummy; } ;
struct pci_epf {struct pci_epf_bar* bar; struct device dev; } ;
struct pci_epc_features {int reserved_bar; int /*<<< orphan*/  align; scalar_t__* bar_fixed_size; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int BAR_5 ; 
 int ENOMEM ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 size_t* bar_size ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct pci_epf_test* epf_get_drvdata (struct pci_epf*) ; 
 void* pci_epf_alloc_space (struct pci_epf*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_epf_test_alloc_space(struct pci_epf *epf)
{
	struct pci_epf_test *epf_test = epf_get_drvdata(epf);
	struct device *dev = &epf->dev;
	struct pci_epf_bar *epf_bar;
	void *base;
	int bar, add;
	enum pci_barno test_reg_bar = epf_test->test_reg_bar;
	const struct pci_epc_features *epc_features;
	size_t test_reg_size;

	epc_features = epf_test->epc_features;

	if (epc_features->bar_fixed_size[test_reg_bar])
		test_reg_size = bar_size[test_reg_bar];
	else
		test_reg_size = sizeof(struct pci_epf_test_reg);

	base = pci_epf_alloc_space(epf, test_reg_size,
				   test_reg_bar, epc_features->align);
	if (!base) {
		dev_err(dev, "Failed to allocated register space\n");
		return -ENOMEM;
	}
	epf_test->reg[test_reg_bar] = base;

	for (bar = BAR_0; bar <= BAR_5; bar += add) {
		epf_bar = &epf->bar[bar];
		add = (epf_bar->flags & PCI_BASE_ADDRESS_MEM_TYPE_64) ? 2 : 1;

		if (bar == test_reg_bar)
			continue;

		if (!!(epc_features->reserved_bar & (1 << bar)))
			continue;

		base = pci_epf_alloc_space(epf, bar_size[bar], bar,
					   epc_features->align);
		if (!base)
			dev_err(dev, "Failed to allocate space for BAR%d\n",
				bar);
		epf_test->reg[bar] = base;
	}

	return 0;
}