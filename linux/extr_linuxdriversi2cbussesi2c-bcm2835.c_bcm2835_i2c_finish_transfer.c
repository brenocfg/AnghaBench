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
struct bcm2835_i2c_dev {scalar_t__ msg_buf_remaining; int /*<<< orphan*/ * msg_buf; scalar_t__ num_msgs; int /*<<< orphan*/ * curr_msg; } ;

/* Variables and functions */

__attribute__((used)) static void bcm2835_i2c_finish_transfer(struct bcm2835_i2c_dev *i2c_dev)
{
	i2c_dev->curr_msg = NULL;
	i2c_dev->num_msgs = 0;

	i2c_dev->msg_buf = NULL;
	i2c_dev->msg_buf_remaining = 0;
}