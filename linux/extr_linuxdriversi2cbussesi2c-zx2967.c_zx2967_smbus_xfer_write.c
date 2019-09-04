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
typedef  int /*<<< orphan*/  u32 ;
struct zx2967_i2c {int error; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_START ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int /*<<< orphan*/  REG_CMD ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_i2c_readl (struct zx2967_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_i2c_writel (struct zx2967_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx2967_smbus_xfer_write(struct zx2967_i2c *i2c)
{
	unsigned long time_left;
	u32 val;

	reinit_completion(&i2c->complete);
	val = zx2967_i2c_readl(i2c, REG_CMD);
	val |= I2C_START;
	zx2967_i2c_writel(i2c, val, REG_CMD);

	time_left = wait_for_completion_timeout(&i2c->complete,
						I2C_TIMEOUT);
	if (time_left == 0)
		return -ETIMEDOUT;

	if (i2c->error)
		return i2c->error;

	return 0;
}