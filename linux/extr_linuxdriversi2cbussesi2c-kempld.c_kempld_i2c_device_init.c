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
typedef  int u8 ;
typedef  int u16 ;
struct kempld_i2c_data {struct kempld_device_data* pld; } ;
struct TYPE_2__ {int spec_major; } ;
struct kempld_device_data {int pld_clock; TYPE_1__ info; } ;

/* Variables and functions */
 int I2C_CMD_IACK ; 
 int I2C_CMD_STOP ; 
 int I2C_CTRL_EN ; 
 int I2C_CTRL_IEN ; 
 int I2C_STAT_BUSY ; 
 int /*<<< orphan*/  KEMPLD_CFG ; 
 int KEMPLD_CFG_GPIO_I2C_MUX ; 
 int /*<<< orphan*/  KEMPLD_I2C_CMD ; 
 int /*<<< orphan*/  KEMPLD_I2C_CTRL ; 
 int KEMPLD_I2C_FREQ_MAX ; 
 int /*<<< orphan*/  KEMPLD_I2C_PREHIGH ; 
 int /*<<< orphan*/  KEMPLD_I2C_PRELOW ; 
 int /*<<< orphan*/  KEMPLD_I2C_STAT ; 
 int bus_frequency ; 
 scalar_t__ i2c_gpio_mux ; 
 int kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_write8 (struct kempld_device_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kempld_i2c_device_init(struct kempld_i2c_data *i2c)
{
	struct kempld_device_data *pld = i2c->pld;
	u16 prescale_corr;
	long prescale;
	u8 ctrl;
	u8 stat;
	u8 cfg;

	/* Make sure the device is disabled */
	ctrl = kempld_read8(pld, KEMPLD_I2C_CTRL);
	ctrl &= ~(I2C_CTRL_EN | I2C_CTRL_IEN);
	kempld_write8(pld, KEMPLD_I2C_CTRL, ctrl);

	if (bus_frequency > KEMPLD_I2C_FREQ_MAX)
		bus_frequency = KEMPLD_I2C_FREQ_MAX;

	if (pld->info.spec_major == 1)
		prescale = pld->pld_clock / (bus_frequency * 5) - 1000;
	else
		prescale = pld->pld_clock / (bus_frequency * 4) - 3000;

	if (prescale < 0)
		prescale = 0;

	/* Round to the best matching value */
	prescale_corr = prescale / 1000;
	if (prescale % 1000 >= 500)
		prescale_corr++;

	kempld_write8(pld, KEMPLD_I2C_PRELOW, prescale_corr & 0xff);
	kempld_write8(pld, KEMPLD_I2C_PREHIGH, prescale_corr >> 8);

	/* Activate I2C bus output on GPIO pins */
	cfg = kempld_read8(pld, KEMPLD_CFG);
	if (i2c_gpio_mux)
		cfg |= KEMPLD_CFG_GPIO_I2C_MUX;
	else
		cfg &= ~KEMPLD_CFG_GPIO_I2C_MUX;
	kempld_write8(pld, KEMPLD_CFG, cfg);

	/* Enable the device */
	kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_IACK);
	ctrl |= I2C_CTRL_EN;
	kempld_write8(pld, KEMPLD_I2C_CTRL, ctrl);

	stat = kempld_read8(pld, KEMPLD_I2C_STAT);
	if (stat & I2C_STAT_BUSY)
		kempld_write8(pld, KEMPLD_I2C_CMD, I2C_CMD_STOP);
}