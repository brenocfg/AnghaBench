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
struct bcm2835_i2c_dev {unsigned int debug_num; int /*<<< orphan*/  debug_num_msgs; struct bcm2835_debug* debug; } ;
struct bcm2835_debug {int /*<<< orphan*/  msg_idx; int /*<<< orphan*/  msg; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 unsigned int BCM2835_DEBUG_MAX ; 
 int /*<<< orphan*/  bcm2835_debug_print_msg (struct bcm2835_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bcm2835_debug_print_status (struct bcm2835_i2c_dev*,struct bcm2835_debug*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void bcm2835_debug_print(struct bcm2835_i2c_dev *i2c_dev)
{
	struct bcm2835_debug *d;
	unsigned int i;

	for (i = 0; i < i2c_dev->debug_num; i++) {
		d = &i2c_dev->debug[i];
		if (d->status == ~0)
			bcm2835_debug_print_msg(i2c_dev, d->msg, d->msg_idx,
				i2c_dev->debug_num_msgs, "start_transfer");
		else
			bcm2835_debug_print_status(i2c_dev, d);
	}
	if (i2c_dev->debug_num >= BCM2835_DEBUG_MAX)
		pr_info("BCM2835_DEBUG_MAX reached\n");
}