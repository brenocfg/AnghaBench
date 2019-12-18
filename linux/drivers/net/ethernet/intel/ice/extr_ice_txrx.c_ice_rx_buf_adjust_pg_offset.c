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
struct ice_rx_buf {unsigned int page_offset; } ;

/* Variables and functions */

__attribute__((used)) static void
ice_rx_buf_adjust_pg_offset(struct ice_rx_buf *rx_buf, unsigned int size)
{
#if (PAGE_SIZE < 8192)
	/* flip page offset to other buffer */
	rx_buf->page_offset ^= size;
#else
	/* move offset up to the next cache line */
	rx_buf->page_offset += size;
#endif
}