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
struct dmar_domain {int /*<<< orphan*/  agaw; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_BIOS_VENDOR ; 
 int /*<<< orphan*/  DMI_BIOS_VERSION ; 
 int /*<<< orphan*/  DMI_PRODUCT_VERSION ; 
 int EIO ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 unsigned long long agaw_to_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dmi_get_system_info (int /*<<< orphan*/ ) ; 
 scalar_t__ hw_pass_through ; 
 int iommu_domain_identity_map (struct dmar_domain*,unsigned long long,unsigned long long) ; 
 struct dmar_domain* si_domain ; 

__attribute__((used)) static int domain_prepare_identity_map(struct device *dev,
				       struct dmar_domain *domain,
				       unsigned long long start,
				       unsigned long long end)
{
	/* For _hardware_ passthrough, don't bother. But for software
	   passthrough, we do it anyway -- it may indicate a memory
	   range which is reserved in E820, so which didn't get set
	   up to start with in si_domain */
	if (domain == si_domain && hw_pass_through) {
		dev_warn(dev, "Ignoring identity map for HW passthrough [0x%Lx - 0x%Lx]\n",
			 start, end);
		return 0;
	}

	dev_info(dev, "Setting identity map [0x%Lx - 0x%Lx]\n", start, end);

	if (end < start) {
		WARN(1, "Your BIOS is broken; RMRR ends before it starts!\n"
			"BIOS vendor: %s; Ver: %s; Product Version: %s\n",
			dmi_get_system_info(DMI_BIOS_VENDOR),
			dmi_get_system_info(DMI_BIOS_VERSION),
		     dmi_get_system_info(DMI_PRODUCT_VERSION));
		return -EIO;
	}

	if (end >> agaw_to_width(domain->agaw)) {
		WARN(1, "Your BIOS is broken; RMRR exceeds permitted address width (%d bits)\n"
		     "BIOS vendor: %s; Ver: %s; Product Version: %s\n",
		     agaw_to_width(domain->agaw),
		     dmi_get_system_info(DMI_BIOS_VENDOR),
		     dmi_get_system_info(DMI_BIOS_VERSION),
		     dmi_get_system_info(DMI_PRODUCT_VERSION));
		return -EIO;
	}

	return iommu_domain_identity_map(domain, start, end);
}