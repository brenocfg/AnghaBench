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
struct device {int dummy; } ;
typedef  int phys_addr_t ;
typedef  long dma_addr_t ;

/* Variables and functions */

dma_addr_t __phys_to_dma(struct device *dev, phys_addr_t paddr)
{
	/* We extract 2bit node id (bit 44~47, only bit 44~45 used now) from
	 * Loongson-3's 48bit address space and embed it into 40bit */
	long nid = (paddr >> 44) & 0x3;
	return ((nid << 44) ^ paddr) | (nid << 37);
}