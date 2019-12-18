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
typedef  scalar_t__ u32 ;
struct zx2967_i2c {int msg_rd; int error; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2C_TIMEOUT ; 
 int /*<<< orphan*/  REG_RDCONF ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zx2967_i2c_empty_rx_fifo (struct zx2967_i2c*,scalar_t__) ; 
 int zx2967_i2c_fill_tx_fifo (struct zx2967_i2c*) ; 
 int /*<<< orphan*/  zx2967_i2c_start_ctrl (struct zx2967_i2c*) ; 
 int /*<<< orphan*/  zx2967_i2c_writel (struct zx2967_i2c*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx2967_i2c_xfer_bytes(struct zx2967_i2c *i2c, u32 bytes)
{
	unsigned long time_left;
	int rd = i2c->msg_rd;
	int ret;

	reinit_completion(&i2c->complete);

	if (rd) {
		zx2967_i2c_writel(i2c, bytes - 1, REG_RDCONF);
	} else {
		ret = zx2967_i2c_fill_tx_fifo(i2c);
		if (ret)
			return ret;
	}

	zx2967_i2c_start_ctrl(i2c);

	time_left = wait_for_completion_timeout(&i2c->complete,
						I2C_TIMEOUT);
	if (time_left == 0)
		return -ETIMEDOUT;

	if (i2c->error)
		return i2c->error;

	return rd ? zx2967_i2c_empty_rx_fifo(i2c, bytes) : 0;
}