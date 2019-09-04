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
struct stm32_dma_desc {int num_sgs; TYPE_1__* sg_req; } ;
struct stm32_dma_chan {size_t mem_burst; size_t mem_width; TYPE_2__* desc; } ;
struct TYPE_4__ {scalar_t__ cyclic; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 size_t stm32_dma_get_remaining_bytes (struct stm32_dma_chan*) ; 

__attribute__((used)) static size_t stm32_dma_desc_residue(struct stm32_dma_chan *chan,
				     struct stm32_dma_desc *desc,
				     u32 next_sg)
{
	u32 modulo, burst_size;
	u32 residue = 0;
	int i;

	/*
	 * In cyclic mode, for the last period, residue = remaining bytes from
	 * NDTR
	 */
	if (chan->desc->cyclic && next_sg == 0) {
		residue = stm32_dma_get_remaining_bytes(chan);
		goto end;
	}

	/*
	 * For all other periods in cyclic mode, and in sg mode,
	 * residue = remaining bytes from NDTR + remaining periods/sg to be
	 * transferred
	 */
	for (i = next_sg; i < desc->num_sgs; i++)
		residue += desc->sg_req[i].len;
	residue += stm32_dma_get_remaining_bytes(chan);

end:
	if (!chan->mem_burst)
		return residue;

	burst_size = chan->mem_burst * chan->mem_width;
	modulo = residue % burst_size;
	if (modulo)
		residue = residue - modulo + burst_size;

	return residue;
}