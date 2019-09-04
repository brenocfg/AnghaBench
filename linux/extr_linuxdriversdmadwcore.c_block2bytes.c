#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {TYPE_1__ chan; } ;
struct dw_dma {TYPE_2__* pdata; } ;
struct TYPE_4__ {scalar_t__ is_idma32; } ;

/* Variables and functions */
 size_t DWC_CTLH_BLOCK_TS (size_t) ; 
 size_t IDMA32C_CTLH_BLOCK_TS (size_t) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t block2bytes(struct dw_dma_chan *dwc, u32 block, u32 width)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);

	if (dw->pdata->is_idma32)
		return IDMA32C_CTLH_BLOCK_TS(block);

	return DWC_CTLH_BLOCK_TS(block) << width;
}