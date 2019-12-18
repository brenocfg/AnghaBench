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
struct sh_flctl {scalar_t__ chan_fifo0_tx; int /*<<< orphan*/ * done_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  FLECFIFO (struct sh_flctl*) ; 
 unsigned long cpu_to_be32 (unsigned long) ; 
 scalar_t__ flctl_dma_fifo0_transfer (struct sh_flctl*,unsigned long*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_wecfifo_ready (struct sh_flctl*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_ec_fiforeg(struct sh_flctl *flctl, int rlen,
						unsigned int offset)
{
	int i, len_4align;
	unsigned long *buf = (unsigned long *)&flctl->done_buff[offset];

	len_4align = (rlen + 3) / 4;

	for (i = 0; i < len_4align; i++)
		buf[i] = cpu_to_be32(buf[i]);

	/* initiate DMA transfer */
	if (flctl->chan_fifo0_tx && rlen >= 32 &&
		flctl_dma_fifo0_transfer(flctl, buf, rlen, DMA_TO_DEVICE) > 0)
			return;	/* DMA success */

	/* do polling transfer */
	for (i = 0; i < len_4align; i++) {
		wait_wecfifo_ready(flctl);
		writel(buf[i], FLECFIFO(flctl));
	}
}