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
struct qup_i2c_block {int rx_fifo_data; int rx_tag_len; int rx_fifo_data_pos; int fifo_available; } ;
struct qup_i2c_dev {scalar_t__ base; struct qup_i2c_block blk; } ;

/* Variables and functions */
 scalar_t__ QUP_IN_FIFO_BASE ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void qup_i2c_recv_tags(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;

	blk->rx_fifo_data = readl(qup->base + QUP_IN_FIFO_BASE);
	blk->rx_fifo_data >>= blk->rx_tag_len  * 8;
	blk->rx_fifo_data_pos = blk->rx_tag_len;
	blk->fifo_available -= blk->rx_tag_len;
}