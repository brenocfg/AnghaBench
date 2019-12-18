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
struct qup_i2c_block {scalar_t__ total_rx_len; scalar_t__ total_tx_len; } ;
struct qup_i2c_dev {scalar_t__ pos; struct qup_i2c_block blk; struct i2c_msg* msg; } ;
struct i2c_msg {scalar_t__ len; } ;

/* Variables and functions */
 int qup_i2c_conf_xfer_v1 (struct qup_i2c_dev*,int) ; 

__attribute__((used)) static int qup_i2c_write_one(struct qup_i2c_dev *qup)
{
	struct i2c_msg *msg = qup->msg;
	struct qup_i2c_block *blk = &qup->blk;

	qup->pos = 0;
	blk->total_tx_len = msg->len + 1;
	blk->total_rx_len = 0;

	return qup_i2c_conf_xfer_v1(qup, false);
}