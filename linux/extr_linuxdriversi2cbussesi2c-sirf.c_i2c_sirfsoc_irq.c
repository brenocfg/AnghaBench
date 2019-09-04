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
struct sirfsoc_i2c {scalar_t__ finished_len; scalar_t__ msg_len; scalar_t__ base; int /*<<< orphan*/  done; scalar_t__ msg_read; TYPE_1__ adapter; int /*<<< orphan*/  err_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SIRFSOC_I2C_CTRL ; 
 int /*<<< orphan*/  SIRFSOC_I2C_ERR_NOACK ; 
 int SIRFSOC_I2C_RESET ; 
 scalar_t__ SIRFSOC_I2C_STATUS ; 
 int SIRFSOC_I2C_STAT_CMD_DONE ; 
 int SIRFSOC_I2C_STAT_ERR ; 
 int SIRFSOC_I2C_STAT_NACK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_sirfsoc_queue_cmd (struct sirfsoc_i2c*) ; 
 int /*<<< orphan*/  i2c_sirfsoc_read_data (struct sirfsoc_i2c*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t i2c_sirfsoc_irq(int irq, void *dev_id)
{
	struct sirfsoc_i2c *siic = (struct sirfsoc_i2c *)dev_id;
	u32 i2c_stat = readl(siic->base + SIRFSOC_I2C_STATUS);

	if (i2c_stat & SIRFSOC_I2C_STAT_ERR) {
		/* Error conditions */
		siic->err_status = SIRFSOC_I2C_ERR_NOACK;
		writel(SIRFSOC_I2C_STAT_ERR, siic->base + SIRFSOC_I2C_STATUS);

		if (i2c_stat & SIRFSOC_I2C_STAT_NACK)
			dev_dbg(&siic->adapter.dev, "ACK not received\n");
		else
			dev_err(&siic->adapter.dev, "I2C error\n");

		/*
		 * Due to hardware ANOMALY, we need to reset I2C earlier after
		 * we get NOACK while accessing non-existing clients, otherwise
		 * we will get errors even we access existing clients later
		 */
		writel(readl(siic->base + SIRFSOC_I2C_CTRL) | SIRFSOC_I2C_RESET,
				siic->base + SIRFSOC_I2C_CTRL);
		while (readl(siic->base + SIRFSOC_I2C_CTRL) & SIRFSOC_I2C_RESET)
			cpu_relax();

		complete(&siic->done);
	} else if (i2c_stat & SIRFSOC_I2C_STAT_CMD_DONE) {
		/* CMD buffer execution complete */
		if (siic->msg_read)
			i2c_sirfsoc_read_data(siic);
		if (siic->finished_len == siic->msg_len)
			complete(&siic->done);
		else /* Fill a new CMD buffer for left data */
			i2c_sirfsoc_queue_cmd(siic);

		writel(SIRFSOC_I2C_STAT_CMD_DONE, siic->base + SIRFSOC_I2C_STATUS);
	}

	return IRQ_HANDLED;
}