#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct axi_dma_chan {TYPE_3__* chip; } ;
typedef  size_t dma_addr_t ;
struct TYPE_6__ {TYPE_2__* dw; } ;
struct TYPE_5__ {TYPE_1__* hdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_data_width; } ;

/* Variables and functions */
 size_t BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ffs (size_t) ; 

__attribute__((used)) static u32 axi_chan_get_xfer_width(struct axi_dma_chan *chan, dma_addr_t src,
				   dma_addr_t dst, size_t len)
{
	u32 max_width = chan->chip->dw->hdata->m_data_width;

	return __ffs(src | dst | len | BIT(max_width));
}