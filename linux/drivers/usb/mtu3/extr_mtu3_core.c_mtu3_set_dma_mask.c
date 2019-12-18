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
typedef  int u32 ;
struct mtu3 {int /*<<< orphan*/  mac_base; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DMA_ADDR_36BIT ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  U3D_MISC_CTRL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int mtu3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtu3_set_dma_mask(struct mtu3 *mtu)
{
	struct device *dev = mtu->dev;
	bool is_36bit = false;
	int ret = 0;
	u32 value;

	value = mtu3_readl(mtu->mac_base, U3D_MISC_CTRL);
	if (value & DMA_ADDR_36BIT) {
		is_36bit = true;
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(36));
		/* If set 36-bit DMA mask fails, fall back to 32-bit DMA mask */
		if (ret) {
			is_36bit = false;
			ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		}
	}
	dev_info(dev, "dma mask: %s bits\n", is_36bit ? "36" : "32");

	return ret;
}