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
struct qup_i2c_block {int send_last_word; int tx_tags_sent; int rx_tags_fetched; int rx_bytes_read; scalar_t__ fifo_available; scalar_t__ rx_fifo_data_pos; scalar_t__ rx_fifo_data; scalar_t__ tx_fifo_free; scalar_t__ tx_fifo_data_pos; scalar_t__ tx_fifo_data; } ;

/* Variables and functions */

__attribute__((used)) static void qup_i2c_clear_blk_v2(struct qup_i2c_block *blk)
{
	blk->send_last_word = false;
	blk->tx_tags_sent = false;
	blk->tx_fifo_data = 0;
	blk->tx_fifo_data_pos = 0;
	blk->tx_fifo_free = 0;

	blk->rx_tags_fetched = false;
	blk->rx_bytes_read = false;
	blk->rx_fifo_data = 0;
	blk->rx_fifo_data_pos = 0;
	blk->fifo_available = 0;
}