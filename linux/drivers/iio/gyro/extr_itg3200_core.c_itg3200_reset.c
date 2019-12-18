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
struct itg3200 {TYPE_1__* i2c; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ITG3200_IRQ_ACTIVE_HIGH ; 
 int ITG3200_IRQ_LATCH_50US_PULSE ; 
 int ITG3200_IRQ_LATCH_CLEAR_ANY ; 
 int ITG3200_IRQ_PUSH_PULL ; 
 int /*<<< orphan*/  ITG3200_REG_IRQ_CONFIG ; 
 int /*<<< orphan*/  ITG3200_REG_POWER_MANAGEMENT ; 
 int ITG3200_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct itg3200* iio_priv (struct iio_dev*) ; 
 int itg3200_write_reg_8 (struct iio_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int itg3200_reset(struct iio_dev *indio_dev)
{
	struct itg3200 *st = iio_priv(indio_dev);
	int ret;

	dev_dbg(&st->i2c->dev, "reset device");

	ret = itg3200_write_reg_8(indio_dev,
			ITG3200_REG_POWER_MANAGEMENT,
			ITG3200_RESET);
	if (ret) {
		dev_err(&st->i2c->dev, "error resetting device");
		goto error_ret;
	}

	/* Wait for PLL (1ms according to datasheet) */
	udelay(1500);

	ret = itg3200_write_reg_8(indio_dev,
			ITG3200_REG_IRQ_CONFIG,
			ITG3200_IRQ_ACTIVE_HIGH |
			ITG3200_IRQ_PUSH_PULL |
			ITG3200_IRQ_LATCH_50US_PULSE |
			ITG3200_IRQ_LATCH_CLEAR_ANY);

	if (ret)
		dev_err(&st->i2c->dev, "error init device");

error_ret:
	return ret;
}