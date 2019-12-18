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
 int fm10k_fifo_tail_offset (struct fm10k_mbx_fifo*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void fm10k_fifo_write_copy(struct fm10k_mbx_fifo *fifo,
				  const u32 *msg, u16 tail_offset, u16 len)
{
	u16 end = fm10k_fifo_tail_offset(fifo, tail_offset);
	u32 *tail = fifo->buffer + end;

	/* track when we should cross the end of the FIFO */
	end = fifo->size - end;

	/* copy end of message before start of message */
	if (end < len)
		memcpy(fifo->buffer, msg + end, (len - end) << 2);
	else
		end = len;

	/* Copy remaining message into Tx FIFO */
	memcpy(tail, msg, end << 2);
}