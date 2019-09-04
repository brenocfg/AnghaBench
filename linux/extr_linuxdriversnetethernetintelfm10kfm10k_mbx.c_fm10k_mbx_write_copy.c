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
typedef  scalar_t__ u16 ;
struct fm10k_mbx_fifo {scalar_t__* buffer; scalar_t__ size; } ;
struct fm10k_mbx_info {int /*<<< orphan*/  tx_mbmem_pulled; int /*<<< orphan*/  pulled; scalar_t__ tail_len; scalar_t__ mbmem_len; scalar_t__ mbmem_reg; struct fm10k_mbx_fifo tx; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ fm10k_fifo_head_offset (struct fm10k_mbx_fifo*,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_mbx_tail_sub (struct fm10k_mbx_info*,scalar_t__) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void fm10k_mbx_write_copy(struct fm10k_hw *hw,
				 struct fm10k_mbx_info *mbx)
{
	struct fm10k_mbx_fifo *fifo = &mbx->tx;
	u32 mbmem = mbx->mbmem_reg;
	u32 *head = fifo->buffer;
	u16 end, len, tail, mask;

	if (!mbx->tail_len)
		return;

	/* determine data length and mbmem tail index */
	mask = mbx->mbmem_len - 1;
	len = mbx->tail_len;
	tail = fm10k_mbx_tail_sub(mbx, len);
	if (tail > mask)
		tail++;

	/* determine offset in the ring */
	end = fm10k_fifo_head_offset(fifo, mbx->pulled);
	head += end;

	/* memory barrier to guarantee data is ready to be read */
	rmb();

	/* Copy message from Tx FIFO */
	for (end = fifo->size - end; len; head = fifo->buffer) {
		do {
			/* adjust tail to match offset for FIFO */
			tail &= mask;
			if (!tail)
				tail++;

			mbx->tx_mbmem_pulled++;

			/* write message to hardware FIFO */
			fm10k_write_reg(hw, mbmem + tail++, *(head++));
		} while (--len && --end);
	}
}