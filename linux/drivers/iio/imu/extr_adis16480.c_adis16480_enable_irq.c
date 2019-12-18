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
typedef  int /*<<< orphan*/  uint16_t ;
struct adis {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16480_DRDY_EN (int) ; 
 int /*<<< orphan*/  ADIS16480_DRDY_EN_MSK ; 
 int /*<<< orphan*/  ADIS16480_REG_FNCTIO_CTRL ; 
 int adis_read_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int adis_write_reg_16 (struct adis*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adis16480_enable_irq(struct adis *adis, bool enable)
{
	uint16_t val;
	int ret;

	ret = adis_read_reg_16(adis, ADIS16480_REG_FNCTIO_CTRL, &val);
	if (ret < 0)
		return ret;

	val &= ~ADIS16480_DRDY_EN_MSK;
	val |= ADIS16480_DRDY_EN(enable);

	return adis_write_reg_16(adis, ADIS16480_REG_FNCTIO_CTRL, val);
}