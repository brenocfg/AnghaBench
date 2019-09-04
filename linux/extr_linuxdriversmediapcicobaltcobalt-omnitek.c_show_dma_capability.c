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
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_HEADER ; 
 int /*<<< orphan*/  CAPABILITY_REGISTER ; 
 int /*<<< orphan*/  CS_REG (int) ; 
 int DMA_TYPE_FIFO ; 
 int /*<<< orphan*/  cobalt_info (char*,...) ; 
 int /*<<< orphan*/  get_dma_direction (int) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_dma_capability(struct cobalt *cobalt)
{
	u32 header = ioread32(CAPABILITY_HEADER);
	u32 capa = ioread32(CAPABILITY_REGISTER);
	u32 i;

	cobalt_info("Omnitek DMA capability: ID 0x%02x Version 0x%02x Next 0x%x Size 0x%x\n",
		    header & 0xff, (header >> 8) & 0xff,
		    (header >> 16) & 0xffff, (capa >> 24) & 0xff);

	switch ((capa >> 8) & 0x3) {
	case 0:
		cobalt_info("Omnitek DMA: 32 bits PCIe and Local\n");
		break;
	case 1:
		cobalt_info("Omnitek DMA: 64 bits PCIe, 32 bits Local\n");
		break;
	case 3:
		cobalt_info("Omnitek DMA: 64 bits PCIe and Local\n");
		break;
	}

	for (i = 0;  i < (capa & 0xf);  i++) {
		u32 status = ioread32(CS_REG(i));

		cobalt_info("Omnitek DMA channel #%d: %s %s\n", i,
			    status & DMA_TYPE_FIFO ? "FIFO" : "MEMORY",
			    get_dma_direction(status));
	}
}