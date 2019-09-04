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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int BMA220_CHIP_ID ; 
 int /*<<< orphan*/  BMA220_REG_ID ; 
 int /*<<< orphan*/  BMA220_REG_SUSPEND ; 
 int BMA220_SUSPEND_WAKE ; 
 int ENODEV ; 
 int bma220_read_reg (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bma220_init(struct spi_device *spi)
{
	int ret;

	ret = bma220_read_reg(spi, BMA220_REG_ID);
	if (ret != BMA220_CHIP_ID)
		return -ENODEV;

	/* Make sure the chip is powered on */
	ret = bma220_read_reg(spi, BMA220_REG_SUSPEND);
	if (ret < 0)
		return ret;
	else if (ret == BMA220_SUSPEND_WAKE)
		return bma220_read_reg(spi, BMA220_REG_SUSPEND);

	return 0;
}