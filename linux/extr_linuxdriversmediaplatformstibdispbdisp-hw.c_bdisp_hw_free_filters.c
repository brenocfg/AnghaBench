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
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  paddr; scalar_t__ virt; } ;

/* Variables and functions */
 int BDISP_HF_NB ; 
 int BDISP_VF_NB ; 
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int NB_H_FILTER ; 
 int NB_V_FILTER ; 
 TYPE_1__* bdisp_h_filter ; 
 int /*<<< orphan*/  dma_free_attrs (struct device*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bdisp_hw_free_filters(struct device *dev)
{
	int size = (BDISP_HF_NB * NB_H_FILTER) + (BDISP_VF_NB * NB_V_FILTER);

	if (bdisp_h_filter[0].virt)
		dma_free_attrs(dev, size, bdisp_h_filter[0].virt,
			       bdisp_h_filter[0].paddr, DMA_ATTR_WRITE_COMBINE);
}