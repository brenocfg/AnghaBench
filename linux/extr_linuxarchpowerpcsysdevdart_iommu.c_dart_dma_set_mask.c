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
typedef  scalar_t__ u64 ;
struct device {scalar_t__* dma_mask; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 int EIO ; 
 scalar_t__ dart_device_on_pcie (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_iommu_ops ; 
 int /*<<< orphan*/  dma_nommu_ops ; 
 int /*<<< orphan*/  dma_supported (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  set_dma_ops (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dart_dma_set_mask(struct device *dev, u64 dma_mask)
{
	if (!dev->dma_mask || !dma_supported(dev, dma_mask))
		return -EIO;

	/* U4 supports a DART bypass, we use it for 64-bit capable
	 * devices to improve performances. However, that only works
	 * for devices connected to U4 own PCIe interface, not bridged
	 * through hypertransport. We need the device to support at
	 * least 40 bits of addresses.
	 */
	if (dart_device_on_pcie(dev) && dma_mask >= DMA_BIT_MASK(40)) {
		dev_info(dev, "Using 64-bit DMA iommu bypass\n");
		set_dma_ops(dev, &dma_nommu_ops);
	} else {
		dev_info(dev, "Using 32-bit DMA via iommu\n");
		set_dma_ops(dev, &dma_iommu_ops);
	}

	*dev->dma_mask = dma_mask;
	return 0;
}