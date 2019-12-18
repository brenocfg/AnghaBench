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
typedef  int /*<<< orphan*/  u32 ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * vaddr; } ;
struct falcon {TYPE_1__ firmware; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void falcon_copy_firmware_image(struct falcon *falcon,
				       const struct firmware *firmware)
{
	u32 *firmware_vaddr = falcon->firmware.vaddr;
	dma_addr_t daddr;
	size_t i;
	int err;

	/* copy the whole thing taking into account endianness */
	for (i = 0; i < firmware->size / sizeof(u32); i++)
		firmware_vaddr[i] = le32_to_cpu(((u32 *)firmware->data)[i]);

	/* ensure that caches are flushed and falcon can see the firmware */
	daddr = dma_map_single(falcon->dev, firmware_vaddr,
			       falcon->firmware.size, DMA_TO_DEVICE);
	err = dma_mapping_error(falcon->dev, daddr);
	if (err) {
		dev_err(falcon->dev, "failed to map firmware: %d\n", err);
		return;
	}
	dma_sync_single_for_device(falcon->dev, daddr,
				   falcon->firmware.size, DMA_TO_DEVICE);
	dma_unmap_single(falcon->dev, daddr, falcon->firmware.size,
			 DMA_TO_DEVICE);
}