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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fm10k_mbx_fifo {int size; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int fm10k_crc_16b (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static u16 fm10k_fifo_crc(struct fm10k_mbx_fifo *fifo, u16 offset,
			  u16 len, u16 seed)
{
	u32 *data = fifo->buffer + offset;

	/* track when we should cross the end of the FIFO */
	offset = fifo->size - offset;

	/* if we are in 2 blocks process the end of the FIFO first */
	if (offset < len) {
		seed = fm10k_crc_16b(data, seed, offset * 2);
		data = fifo->buffer;
		len -= offset;
	}

	/* process any remaining bits */
	return fm10k_crc_16b(data, seed, len * 2);
}