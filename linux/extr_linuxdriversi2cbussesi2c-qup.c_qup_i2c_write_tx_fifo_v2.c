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
struct qup_i2c_block {int tx_tags_sent; int send_last_word; int /*<<< orphan*/  tx_fifo_data; scalar_t__ tx_fifo_free; int /*<<< orphan*/  tx_fifo_data_pos; int /*<<< orphan*/  cur_blk_len; int /*<<< orphan*/  cur_data; int /*<<< orphan*/  tx_tag_len; int /*<<< orphan*/  cur_tx_tags; } ;
struct qup_i2c_dev {scalar_t__ base; struct qup_i2c_block blk; } ;

/* Variables and functions */
 scalar_t__ QUP_OUT_FIFO_BASE ; 
 int /*<<< orphan*/  qup_i2c_write_blk_data (struct qup_i2c_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qup_i2c_write_tx_fifo_v2(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;

	if (!blk->tx_tags_sent) {
		qup_i2c_write_blk_data(qup, &blk->cur_tx_tags,
				       &blk->tx_tag_len);
		blk->tx_tags_sent = true;
	}

	if (blk->send_last_word)
		goto send_last_word;

	qup_i2c_write_blk_data(qup, &blk->cur_data, &blk->cur_blk_len);
	if (!blk->cur_blk_len) {
		if (!blk->tx_fifo_data_pos)
			return;

		if (blk->tx_fifo_free)
			goto send_last_word;

		blk->send_last_word = true;
	}

	return;

send_last_word:
	writel(blk->tx_fifo_data, qup->base + QUP_OUT_FIFO_BASE);
}