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
typedef  scalar_t__ u32 ;
struct xilinx_dma_chan {scalar_t__ desc_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_write (struct xilinx_dma_chan*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void vdma_desc_write(struct xilinx_dma_chan *chan, u32 reg,
				   u32 value)
{
	dma_write(chan, chan->desc_offset + reg, value);
}