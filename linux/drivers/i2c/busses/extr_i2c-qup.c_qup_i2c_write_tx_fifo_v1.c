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
struct qup_i2c_block {scalar_t__ tx_fifo_free; } ;
struct qup_i2c_dev {int pos; scalar_t__ base; struct i2c_msg* msg; struct qup_i2c_block blk; } ;
struct i2c_msg {int len; int* buf; } ;

/* Variables and functions */
 int QUP_MSW_SHIFT ; 
 scalar_t__ QUP_OUT_FIFO_BASE ; 
 int QUP_TAG_DATA ; 
 int QUP_TAG_START ; 
 int QUP_TAG_STOP ; 
 int i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void qup_i2c_write_tx_fifo_v1(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;
	struct i2c_msg *msg = qup->msg;
	u32 addr = i2c_8bit_addr_from_msg(msg);
	u32 qup_tag;
	int idx;
	u32 val;

	if (qup->pos == 0) {
		val = QUP_TAG_START | addr;
		idx = 1;
		blk->tx_fifo_free--;
	} else {
		val = 0;
		idx = 0;
	}

	while (blk->tx_fifo_free && qup->pos < msg->len) {
		if (qup->pos == msg->len - 1)
			qup_tag = QUP_TAG_STOP;
		else
			qup_tag = QUP_TAG_DATA;

		if (idx & 1)
			val |= (qup_tag | msg->buf[qup->pos]) << QUP_MSW_SHIFT;
		else
			val = qup_tag | msg->buf[qup->pos];

		/* Write out the pair and the last odd value */
		if (idx & 1 || qup->pos == msg->len - 1)
			writel(val, qup->base + QUP_OUT_FIFO_BASE);

		qup->pos++;
		idx++;
		blk->tx_fifo_free--;
	}
}