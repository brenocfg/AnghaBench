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
struct wmt_i2c_dev {scalar_t__ mode; scalar_t__ base; int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CR_ENABLE ; 
 scalar_t__ I2C_MODE_STANDARD ; 
 int IMR_ENABLE_ALL ; 
 int ISR_WRITE_ALL ; 
 int MCR_APB_166M ; 
 scalar_t__ REG_CR ; 
 scalar_t__ REG_CSR ; 
 scalar_t__ REG_IMR ; 
 scalar_t__ REG_ISR ; 
 scalar_t__ REG_MCR ; 
 scalar_t__ REG_TR ; 
 int SCL_TIMEOUT (int) ; 
 int TR_HS ; 
 int TR_STD ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int wmt_i2c_reset_hardware(struct wmt_i2c_dev *i2c_dev)
{
	int err;

	err = clk_prepare_enable(i2c_dev->clk);
	if (err) {
		dev_err(i2c_dev->dev, "failed to enable clock\n");
		return err;
	}

	err = clk_set_rate(i2c_dev->clk, 20000000);
	if (err) {
		dev_err(i2c_dev->dev, "failed to set clock = 20Mhz\n");
		clk_disable_unprepare(i2c_dev->clk);
		return err;
	}

	writew(0, i2c_dev->base + REG_CR);
	writew(MCR_APB_166M, i2c_dev->base + REG_MCR);
	writew(ISR_WRITE_ALL, i2c_dev->base + REG_ISR);
	writew(IMR_ENABLE_ALL, i2c_dev->base + REG_IMR);
	writew(CR_ENABLE, i2c_dev->base + REG_CR);
	readw(i2c_dev->base + REG_CSR);		/* read clear */
	writew(ISR_WRITE_ALL, i2c_dev->base + REG_ISR);

	if (i2c_dev->mode == I2C_MODE_STANDARD)
		writew(SCL_TIMEOUT(128) | TR_STD, i2c_dev->base + REG_TR);
	else
		writew(SCL_TIMEOUT(128) | TR_HS, i2c_dev->base + REG_TR);

	return 0;
}