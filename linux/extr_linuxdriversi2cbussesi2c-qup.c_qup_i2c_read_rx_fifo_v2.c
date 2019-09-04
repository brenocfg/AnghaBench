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
struct qup_i2c_block {int rx_tags_fetched; int rx_bytes_read; int /*<<< orphan*/  cur_blk_len; } ;
struct qup_i2c_dev {struct qup_i2c_block blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  qup_i2c_recv_data (struct qup_i2c_dev*) ; 
 int /*<<< orphan*/  qup_i2c_recv_tags (struct qup_i2c_dev*) ; 

__attribute__((used)) static void qup_i2c_read_rx_fifo_v2(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;

	if (!blk->rx_tags_fetched) {
		qup_i2c_recv_tags(qup);
		blk->rx_tags_fetched = true;
	}

	qup_i2c_recv_data(qup);
	if (!blk->cur_blk_len)
		blk->rx_bytes_read = true;
}