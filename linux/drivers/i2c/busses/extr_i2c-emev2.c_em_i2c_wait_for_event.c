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
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct em_i2c_device {scalar_t__ base; TYPE_1__ adap; int /*<<< orphan*/  msg_done; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int I2C_BIT_ALD0 ; 
 scalar_t__ I2C_OFS_IICSE0 ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_i2c_wait_for_event(struct em_i2c_device *priv)
{
	unsigned long time_left;
	int status;

	reinit_completion(&priv->msg_done);

	time_left = wait_for_completion_timeout(&priv->msg_done, priv->adap.timeout);

	if (!time_left)
		return -ETIMEDOUT;

	status = readb(priv->base + I2C_OFS_IICSE0);
	return status & I2C_BIT_ALD0 ? -EAGAIN : status;
}