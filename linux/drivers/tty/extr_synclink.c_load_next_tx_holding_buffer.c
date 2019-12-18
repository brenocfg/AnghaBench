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
struct tx_holding_buffer {int buffer_size; int /*<<< orphan*/  buffer; } ;
struct mgsl_struct {size_t get_tx_holding_index; int xmit_cnt; size_t num_tx_holding_buffers; int /*<<< orphan*/  tx_timer; scalar_t__ tx_holding_count; struct tx_holding_buffer* tx_holding_buffers; } ;

/* Variables and functions */
 int DMABUFFERSIZE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mgsl_load_tx_dma_buffer (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int num_free_tx_dma_buffers (struct mgsl_struct*) ; 

__attribute__((used)) static bool load_next_tx_holding_buffer(struct mgsl_struct *info)
{
	bool ret = false;

	if ( info->tx_holding_count ) {
		/* determine if we have enough tx dma buffers
		 * to accommodate the next tx frame
		 */
		struct tx_holding_buffer *ptx =
			&info->tx_holding_buffers[info->get_tx_holding_index];
		int num_free = num_free_tx_dma_buffers(info);
		int num_needed = ptx->buffer_size / DMABUFFERSIZE;
		if ( ptx->buffer_size % DMABUFFERSIZE )
			++num_needed;

		if (num_needed <= num_free) {
			info->xmit_cnt = ptx->buffer_size;
			mgsl_load_tx_dma_buffer(info,ptx->buffer,ptx->buffer_size);

			--info->tx_holding_count;
			if ( ++info->get_tx_holding_index >= info->num_tx_holding_buffers)
				info->get_tx_holding_index=0;

			/* restart transmit timer */
			mod_timer(&info->tx_timer, jiffies + msecs_to_jiffies(5000));

			ret = true;
		}
	}

	return ret;
}