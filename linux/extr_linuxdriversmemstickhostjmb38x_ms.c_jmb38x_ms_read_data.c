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
struct jmb38x_ms_host {int io_pos; int* io_word; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ DATA ; 
 scalar_t__ STATUS ; 
 int STATUS_FIFO_EMPTY ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int jmb38x_ms_read_data(struct jmb38x_ms_host *host,
					unsigned char *buf, unsigned int length)
{
	unsigned int off = 0;

	while (host->io_pos && length) {
		buf[off++] = host->io_word[0] & 0xff;
		host->io_word[0] >>= 8;
		length--;
		host->io_pos--;
	}

	if (!length)
		return off;

	while (!(STATUS_FIFO_EMPTY & readl(host->addr + STATUS))) {
		if (length < 4)
			break;
		*(unsigned int *)(buf + off) = __raw_readl(host->addr + DATA);
		length -= 4;
		off += 4;
	}

	if (length
	    && !(STATUS_FIFO_EMPTY & readl(host->addr + STATUS))) {
		host->io_word[0] = readl(host->addr + DATA);
		for (host->io_pos = 4; host->io_pos; --host->io_pos) {
			buf[off++] = host->io_word[0] & 0xff;
			host->io_word[0] >>= 8;
			length--;
			if (!length)
				break;
		}
	}

	return off;
}