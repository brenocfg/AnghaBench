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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct sirfsoc_i2c {scalar_t__ err_status; scalar_t__ base; TYPE_1__ adapter; int /*<<< orphan*/  done; } ;
struct i2c_msg {int len; } ;

/* Variables and functions */
 int EAGAIN ; 
 int SIRFSOC_I2C_CMD_DONE_EN ; 
 scalar_t__ SIRFSOC_I2C_CMD_START ; 
 scalar_t__ SIRFSOC_I2C_CTRL ; 
 int SIRFSOC_I2C_ERR_INT_EN ; 
 scalar_t__ SIRFSOC_I2C_ERR_TIMEOUT ; 
 int SIRFSOC_I2C_RESET ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_sirfsoc_queue_cmd (struct sirfsoc_i2c*) ; 
 int /*<<< orphan*/  i2c_sirfsoc_set_address (struct sirfsoc_i2c*,struct i2c_msg*) ; 
 int msecs_to_jiffies (int) ; 
 int readl (scalar_t__) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i2c_sirfsoc_xfer_msg(struct sirfsoc_i2c *siic, struct i2c_msg *msg)
{
	u32 regval = readl(siic->base + SIRFSOC_I2C_CTRL);
	/* timeout waiting for the xfer to finish or fail */
	int timeout = msecs_to_jiffies((msg->len + 1) * 50);

	i2c_sirfsoc_set_address(siic, msg);

	writel(regval | SIRFSOC_I2C_CMD_DONE_EN | SIRFSOC_I2C_ERR_INT_EN,
		siic->base + SIRFSOC_I2C_CTRL);
	i2c_sirfsoc_queue_cmd(siic);

	if (wait_for_completion_timeout(&siic->done, timeout) == 0) {
		siic->err_status = SIRFSOC_I2C_ERR_TIMEOUT;
		dev_err(&siic->adapter.dev, "Transfer timeout\n");
	}

	writel(regval & ~(SIRFSOC_I2C_CMD_DONE_EN | SIRFSOC_I2C_ERR_INT_EN),
		siic->base + SIRFSOC_I2C_CTRL);
	writel(0, siic->base + SIRFSOC_I2C_CMD_START);

	/* i2c control doesn't response, reset it */
	if (siic->err_status == SIRFSOC_I2C_ERR_TIMEOUT) {
		writel(readl(siic->base + SIRFSOC_I2C_CTRL) | SIRFSOC_I2C_RESET,
			siic->base + SIRFSOC_I2C_CTRL);
		while (readl(siic->base + SIRFSOC_I2C_CTRL) & SIRFSOC_I2C_RESET)
			cpu_relax();
	}
	return siic->err_status ? -EAGAIN : 0;
}