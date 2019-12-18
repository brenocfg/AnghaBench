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
typedef  int u32 ;
typedef  int u16 ;
struct fm10k_mbx_fifo {int* buffer; int size; } ;
struct fm10k_mbx_info {int mbmem_reg; int mbmem_len; int head_len; int /*<<< orphan*/  rx_mbmem_pushed; int /*<<< orphan*/  pushed; struct fm10k_mbx_fifo rx; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int fm10k_fifo_tail_offset (struct fm10k_mbx_fifo*,int /*<<< orphan*/ ) ; 
 int fm10k_mbx_head_sub (struct fm10k_mbx_info*,int) ; 
 int /*<<< orphan*/  fm10k_read_reg (struct fm10k_hw*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void fm10k_mbx_read_copy(struct fm10k_hw *hw,
				struct fm10k_mbx_info *mbx)
{
	struct fm10k_mbx_fifo *fifo = &mbx->rx;
	u32 mbmem = mbx->mbmem_reg ^ mbx->mbmem_len;
	u32 *tail = fifo->buffer;
	u16 end, len, head;

	/* determine data length and mbmem head index */
	len = mbx->head_len;
	head = fm10k_mbx_head_sub(mbx, len);
	if (head >= mbx->mbmem_len)
		head++;

	/* determine offset in the ring */
	end = fm10k_fifo_tail_offset(fifo, mbx->pushed);
	tail += end;

	/* Copy message into Rx FIFO */
	for (end = fifo->size - end; len; tail = fifo->buffer) {
		do {
			/* adjust head to match offset for FIFO */
			head &= mbx->mbmem_len - 1;
			if (!head)
				head++;

			mbx->rx_mbmem_pushed++;

			/* read message from hardware FIFO */
			*(tail++) = fm10k_read_reg(hw, mbmem + head++);
		} while (--len && --end);
	}

	/* memory barrier to guarantee FIFO is written before tail update */
	wmb();
}