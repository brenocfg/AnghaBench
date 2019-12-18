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
struct qup_i2c_block {int rx_bytes_read; scalar_t__ fifo_available; scalar_t__ tx_fifo_free; } ;

/* Variables and functions */

__attribute__((used)) static void qup_i2c_clear_blk_v1(struct qup_i2c_block *blk)
{
	blk->tx_fifo_free = 0;
	blk->fifo_available = 0;
	blk->rx_bytes_read = false;
}