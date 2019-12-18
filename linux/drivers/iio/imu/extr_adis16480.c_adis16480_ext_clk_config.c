#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct device_node {int dummy; } ;
struct TYPE_7__ {TYPE_1__* spi; } ;
struct adis16480 {int /*<<< orphan*/  ext_clk; TYPE_3__ adis; int /*<<< orphan*/  clk_mode; TYPE_2__* chip_info; } ;
typedef  enum adis16480_int_pin { ____Placeholder_adis16480_int_pin } adis16480_int_pin ;
struct TYPE_6__ {scalar_t__ has_pps_clk_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADIS16480_DRDY_SEL (unsigned int) ; 
 int /*<<< orphan*/  ADIS16480_REG_FNCTIO_CTRL ; 
 unsigned int ADIS16480_SYNC_EN (int) ; 
 unsigned int ADIS16480_SYNC_EN_MSK ; 
 unsigned int ADIS16480_SYNC_MODE (int /*<<< orphan*/ ) ; 
 unsigned int ADIS16480_SYNC_MODE_MSK ; 
 unsigned int ADIS16480_SYNC_SEL (int) ; 
 unsigned int ADIS16480_SYNC_SEL_MSK ; 
 int adis16480_of_get_ext_clk_pin (struct adis16480*,struct device_node*) ; 
 int adis_read_reg_16 (TYPE_3__*,int /*<<< orphan*/ ,unsigned int*) ; 
 int adis_write_reg_16 (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int adis16480_ext_clk_config(struct adis16480 *st,
				    struct device_node *of_node,
				    bool enable)
{
	unsigned int mode, mask;
	enum adis16480_int_pin pin;
	uint16_t val;
	int ret;

	ret = adis_read_reg_16(&st->adis, ADIS16480_REG_FNCTIO_CTRL, &val);
	if (ret < 0)
		return ret;

	pin = adis16480_of_get_ext_clk_pin(st, of_node);
	/*
	 * Each DIOx pin supports only one function at a time. When a single pin
	 * has two assignments, the enable bit for a lower priority function
	 * automatically resets to zero (disabling the lower priority function).
	 */
	if (pin == ADIS16480_DRDY_SEL(val))
		dev_warn(&st->adis.spi->dev,
			"DIO%x pin supports only one function at a time\n",
			pin + 1);

	mode = ADIS16480_SYNC_EN(enable) | ADIS16480_SYNC_SEL(pin);
	mask = ADIS16480_SYNC_EN_MSK | ADIS16480_SYNC_SEL_MSK;
	/* Only ADIS1649x devices support pps ext clock mode */
	if (st->chip_info->has_pps_clk_mode) {
		mode |= ADIS16480_SYNC_MODE(st->clk_mode);
		mask |= ADIS16480_SYNC_MODE_MSK;
	}

	val &= ~mask;
	val |= mode;

	ret = adis_write_reg_16(&st->adis, ADIS16480_REG_FNCTIO_CTRL, val);
	if (ret < 0)
		return ret;

	return clk_prepare_enable(st->ext_clk);
}