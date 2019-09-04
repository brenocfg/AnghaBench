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
typedef  unsigned int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct dw_dma_chan {size_t block_size; TYPE_1__ chan; } ;
struct dw_dma {TYPE_2__* pdata; } ;
struct TYPE_4__ {scalar_t__ is_idma32; } ;

/* Variables and functions */
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bytes2block(struct dw_dma_chan *dwc, size_t bytes,
			  unsigned int width, size_t *len)
{
	struct dw_dma *dw = to_dw_dma(dwc->chan.device);
	u32 block;

	/* Always in bytes for iDMA 32-bit */
	if (dw->pdata->is_idma32)
		width = 0;

	if ((bytes >> width) > dwc->block_size) {
		block = dwc->block_size;
		*len = block << width;
	} else {
		block = bytes >> width;
		*len = bytes;
	}

	return block;
}