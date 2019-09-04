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
typedef  int dma_addr_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static inline dma_addr_t vb2_dc_pfn_to_dma(struct device *dev, unsigned long pfn)
{
	/* really, we cannot do anything better at this point */
	return (dma_addr_t)(pfn) << PAGE_SHIFT;
}