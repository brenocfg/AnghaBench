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
struct gpmi_nand_data {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_page_end(struct gpmi_nand_data *this,
			const void *source, unsigned length,
			void *alt_virt, dma_addr_t alt_phys, unsigned alt_size,
			const void *used_virt, dma_addr_t used_phys)
{
	struct device *dev = this->dev;
	if (used_virt == source)
		dma_unmap_single(dev, used_phys, length, DMA_TO_DEVICE);
}