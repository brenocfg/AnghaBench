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
struct qup_i2c_block {int rx_bytes_read; scalar_t__ fifo_available; } ;
struct qup_i2c_dev {scalar_t__ pos; scalar_t__ base; struct i2c_msg* msg; struct qup_i2c_block blk; } ;
struct i2c_msg {scalar_t__ len; int* buf; } ;

/* Variables and functions */
 scalar_t__ QUP_IN_FIFO_BASE ; 
 int QUP_MSW_SHIFT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static void qup_i2c_read_rx_fifo_v1(struct qup_i2c_dev *qup)
{
	struct qup_i2c_block *blk = &qup->blk;
	struct i2c_msg *msg = qup->msg;
	u32 val = 0;
	int idx = 0;

	while (blk->fifo_available && qup->pos < msg->len) {
		if ((idx & 1) == 0) {
			/* Reading 2 words at time */
			val = readl(qup->base + QUP_IN_FIFO_BASE);
			msg->buf[qup->pos++] = val & 0xFF;
		} else {
			msg->buf[qup->pos++] = val >> QUP_MSW_SHIFT;
		}
		idx++;
		blk->fifo_available--;
	}

	if (qup->pos == msg->len)
		blk->rx_bytes_read = true;
}