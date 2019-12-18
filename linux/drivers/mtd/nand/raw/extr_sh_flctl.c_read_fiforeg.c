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
struct sh_flctl {scalar_t__ chan_fifo0_rx; int /*<<< orphan*/ * done_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  FLDTFIFO (struct sh_flctl*) ; 
 unsigned long be32_to_cpu (unsigned long) ; 
 scalar_t__ flctl_dma_fifo0_transfer (struct sh_flctl*,unsigned long*,int,int /*<<< orphan*/ ) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_rfifo_ready (struct sh_flctl*) ; 

__attribute__((used)) static void read_fiforeg(struct sh_flctl *flctl, int rlen, int offset)
{
	int i, len_4align;
	unsigned long *buf = (unsigned long *)&flctl->done_buff[offset];

	len_4align = (rlen + 3) / 4;

	/* initiate DMA transfer */
	if (flctl->chan_fifo0_rx && rlen >= 32 &&
		flctl_dma_fifo0_transfer(flctl, buf, rlen, DMA_FROM_DEVICE) > 0)
			goto convert;	/* DMA success */

	/* do polling transfer */
	for (i = 0; i < len_4align; i++) {
		wait_rfifo_ready(flctl);
		buf[i] = readl(FLDTFIFO(flctl));
	}

convert:
	for (i = 0; i < len_4align; i++)
		buf[i] = be32_to_cpu(buf[i]);
}