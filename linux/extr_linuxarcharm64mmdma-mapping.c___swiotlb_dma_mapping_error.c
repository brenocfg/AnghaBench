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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ swiotlb ; 
 int swiotlb_dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __swiotlb_dma_mapping_error(struct device *hwdev, dma_addr_t addr)
{
	if (swiotlb)
		return swiotlb_dma_mapping_error(hwdev, addr);
	return 0;
}