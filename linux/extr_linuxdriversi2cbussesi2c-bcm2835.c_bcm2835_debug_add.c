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
typedef  int /*<<< orphan*/  u32 ;
struct bcm2835_i2c_dev {size_t debug_num; TYPE_1__* debug; int /*<<< orphan*/  msg_buf_remaining; scalar_t__ num_msgs; scalar_t__ debug_num_msgs; int /*<<< orphan*/  curr_msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  remain; scalar_t__ msg_idx; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 size_t BCM2835_DEBUG_MAX ; 

__attribute__((used)) static inline void bcm2835_debug_add(struct bcm2835_i2c_dev *i2c_dev, u32 s)
{
	if (!i2c_dev->debug_num_msgs || i2c_dev->debug_num >= BCM2835_DEBUG_MAX)
		return;

	i2c_dev->debug[i2c_dev->debug_num].msg = i2c_dev->curr_msg;
	i2c_dev->debug[i2c_dev->debug_num].msg_idx =
				i2c_dev->debug_num_msgs - i2c_dev->num_msgs;
	i2c_dev->debug[i2c_dev->debug_num].remain = i2c_dev->msg_buf_remaining;
	i2c_dev->debug[i2c_dev->debug_num].status = s;
	i2c_dev->debug_num++;
}