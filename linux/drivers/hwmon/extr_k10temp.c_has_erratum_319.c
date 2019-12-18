#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int x86; int x86_model; int x86_stepping; } ;

/* Variables and functions */
 int CPUID_PKGTYPE_AM2R2_AM3 ; 
 int CPUID_PKGTYPE_F ; 
 int CPUID_PKGTYPE_MASK ; 
 int DDR3_MODE ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DCT0_CONFIG_HIGH ; 
 TYPE_1__ boot_cpu_data ; 
 int cpuid_ebx (int) ; 
 int /*<<< orphan*/  pci_bus_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool has_erratum_319(struct pci_dev *pdev)
{
	u32 pkg_type, reg_dram_cfg;

	if (boot_cpu_data.x86 != 0x10)
		return false;

	/*
	 * Erratum 319: The thermal sensor of Socket F/AM2+ processors
	 *              may be unreliable.
	 */
	pkg_type = cpuid_ebx(0x80000001) & CPUID_PKGTYPE_MASK;
	if (pkg_type == CPUID_PKGTYPE_F)
		return true;
	if (pkg_type != CPUID_PKGTYPE_AM2R2_AM3)
		return false;

	/* DDR3 memory implies socket AM3, which is good */
	pci_bus_read_config_dword(pdev->bus,
				  PCI_DEVFN(PCI_SLOT(pdev->devfn), 2),
				  REG_DCT0_CONFIG_HIGH, &reg_dram_cfg);
	if (reg_dram_cfg & DDR3_MODE)
		return false;

	/*
	 * Unfortunately it is possible to run a socket AM3 CPU with DDR2
	 * memory. We blacklist all the cores which do exist in socket AM2+
	 * format. It still isn't perfect, as RB-C2 cores exist in both AM2+
	 * and AM3 formats, but that's the best we can do.
	 */
	return boot_cpu_data.x86_model < 4 ||
	       (boot_cpu_data.x86_model == 4 && boot_cpu_data.x86_stepping <= 2);
}