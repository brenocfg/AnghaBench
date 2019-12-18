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
struct parport {int modes; } ;

/* Variables and functions */
 int PARPORT_MODE_DMA ; 
 size_t parport_ip32_fifo_write_block_dma (struct parport*,void const*,size_t) ; 
 size_t parport_ip32_fifo_write_block_pio (struct parport*,void const*,size_t) ; 

__attribute__((used)) static size_t parport_ip32_fifo_write_block(struct parport *p,
					    const void *buf, size_t len)
{
	size_t written = 0;
	if (len)
		/* FIXME - Maybe some threshold value should be set for @len
		 * under which we revert to PIO mode? */
		written = (p->modes & PARPORT_MODE_DMA) ?
			parport_ip32_fifo_write_block_dma(p, buf, len) :
			parport_ip32_fifo_write_block_pio(p, buf, len);
	return written;
}