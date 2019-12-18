#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_8__ {unsigned int paddr; void* virt; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_7__ {int /*<<< orphan*/  coef; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_6__ {unsigned int paddr; void* virt; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_5__ {int /*<<< orphan*/  coef; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 unsigned int BDISP_HF_NB ; 
 unsigned int BDISP_VF_NB ; 
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int NB_H_FILTER ; 
 unsigned int NB_V_FILTER ; 
 TYPE_4__* bdisp_h_filter ; 
 TYPE_3__* bdisp_h_spec ; 
 TYPE_2__* bdisp_v_filter ; 
 TYPE_1__* bdisp_v_spec ; 
 void* dma_alloc_attrs (struct device*,unsigned int,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,unsigned int) ; 

int bdisp_hw_alloc_filters(struct device *dev)
{
	unsigned int i, size;
	void *base;
	dma_addr_t paddr;

	/* Allocate all the filters within a single memory page */
	size = (BDISP_HF_NB * NB_H_FILTER) + (BDISP_VF_NB * NB_V_FILTER);
	base = dma_alloc_attrs(dev, size, &paddr, GFP_KERNEL,
			       DMA_ATTR_WRITE_COMBINE);
	if (!base)
		return -ENOMEM;

	/* Setup filter addresses */
	for (i = 0; i < NB_H_FILTER; i++) {
		bdisp_h_filter[i].min = bdisp_h_spec[i].min;
		bdisp_h_filter[i].max = bdisp_h_spec[i].max;
		memcpy(base, bdisp_h_spec[i].coef, BDISP_HF_NB);
		bdisp_h_filter[i].virt = base;
		bdisp_h_filter[i].paddr = paddr;
		base += BDISP_HF_NB;
		paddr += BDISP_HF_NB;
	}

	for (i = 0; i < NB_V_FILTER; i++) {
		bdisp_v_filter[i].min = bdisp_v_spec[i].min;
		bdisp_v_filter[i].max = bdisp_v_spec[i].max;
		memcpy(base, bdisp_v_spec[i].coef, BDISP_VF_NB);
		bdisp_v_filter[i].virt = base;
		bdisp_v_filter[i].paddr = paddr;
		base += BDISP_VF_NB;
		paddr += BDISP_VF_NB;
	}

	return 0;
}