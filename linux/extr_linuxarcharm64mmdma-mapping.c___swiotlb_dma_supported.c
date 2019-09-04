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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ swiotlb ; 
 int swiotlb_dma_supported (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __swiotlb_dma_supported(struct device *hwdev, u64 mask)
{
	if (swiotlb)
		return swiotlb_dma_supported(hwdev, mask);
	return 1;
}