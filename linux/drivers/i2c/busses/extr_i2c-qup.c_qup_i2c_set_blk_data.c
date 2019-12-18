#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  data_len; scalar_t__ pos; } ;
struct qup_i2c_dev {int /*<<< orphan*/  blk_xfer_limit; TYPE_1__ blk; } ;
struct i2c_msg {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qup_i2c_set_blk_data(struct qup_i2c_dev *qup,
				 struct i2c_msg *msg)
{
	qup->blk.pos = 0;
	qup->blk.data_len = msg->len;
	qup->blk.count = DIV_ROUND_UP(msg->len, qup->blk_xfer_limit);
}