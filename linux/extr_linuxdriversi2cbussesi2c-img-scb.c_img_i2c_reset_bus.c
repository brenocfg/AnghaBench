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
struct img_i2c {int /*<<< orphan*/  msg_complete; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IMG_I2C_TIMEOUT ; 
 int /*<<< orphan*/  img_i2c_reset_start (struct img_i2c*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int img_i2c_reset_bus(struct img_i2c *i2c)
{
	unsigned long flags;
	unsigned long time_left;

	spin_lock_irqsave(&i2c->lock, flags);
	reinit_completion(&i2c->msg_complete);
	img_i2c_reset_start(i2c);
	spin_unlock_irqrestore(&i2c->lock, flags);

	time_left = wait_for_completion_timeout(&i2c->msg_complete,
					      IMG_I2C_TIMEOUT);
	if (time_left == 0)
		return -ETIMEDOUT;
	return 0;
}