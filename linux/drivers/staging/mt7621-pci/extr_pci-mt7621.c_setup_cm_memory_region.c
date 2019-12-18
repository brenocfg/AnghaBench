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
struct resource {int end; int start; } ;
struct mt7621_pcie {struct device* dev; struct resource mem; } ;
struct device {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int CM_GCR_REGn_MASK_CMTGT_IOCU0 ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,unsigned long long,unsigned long long) ; 
 scalar_t__ mips_cps_numiocu (int /*<<< orphan*/ ) ; 
 scalar_t__ read_gcr_reg1_base () ; 
 scalar_t__ read_gcr_reg1_mask () ; 
 int /*<<< orphan*/  write_gcr_reg1_base (int) ; 
 int /*<<< orphan*/  write_gcr_reg1_mask (int) ; 

__attribute__((used)) static void setup_cm_memory_region(struct mt7621_pcie *pcie)
{
	struct resource *mem_resource = &pcie->mem;
	struct device *dev = pcie->dev;
	resource_size_t mask;

	if (mips_cps_numiocu(0)) {
		/*
		 * FIXME: hardware doesn't accept mask values with 1s after
		 * 0s (e.g. 0xffef), so it would be great to warn if that's
		 * about to happen
		 */
		mask = ~(mem_resource->end - mem_resource->start);

		write_gcr_reg1_base(mem_resource->start);
		write_gcr_reg1_mask(mask | CM_GCR_REGn_MASK_CMTGT_IOCU0);
		dev_info(dev, "PCI coherence region base: 0x%08llx, mask/settings: 0x%08llx\n",
			(unsigned long long)read_gcr_reg1_base(),
			(unsigned long long)read_gcr_reg1_mask());
	}
}