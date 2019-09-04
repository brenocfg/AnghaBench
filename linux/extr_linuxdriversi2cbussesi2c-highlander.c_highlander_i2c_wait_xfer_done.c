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
struct highlander_i2c_dev {int /*<<< orphan*/  cmd_complete; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  highlander_i2c_poll (struct highlander_i2c_dev*) ; 
 int highlander_i2c_wait_for_ack (struct highlander_i2c_dev*) ; 
 int /*<<< orphan*/  iic_timeout ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int highlander_i2c_wait_xfer_done(struct highlander_i2c_dev *dev)
{
	if (dev->irq)
		wait_for_completion_timeout(&dev->cmd_complete,
					  msecs_to_jiffies(iic_timeout));
	else
		/* busy looping, the IRQ of champions */
		highlander_i2c_poll(dev);

	return highlander_i2c_wait_for_ack(dev);
}