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
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD9523_EEPROM_CTRL1 ; 
 int /*<<< orphan*/  AD9523_EEPROM_CTRL1_EEPROM_WRITE_PROT_DIS ; 
 int /*<<< orphan*/  AD9523_EEPROM_CTRL2 ; 
 int /*<<< orphan*/  AD9523_EEPROM_CTRL2_REG2EEPROM ; 
 int AD9523_EEPROM_DATA_XFER_IN_PROGRESS ; 
 int /*<<< orphan*/  AD9523_EEPROM_DATA_XFER_STATUS ; 
 int /*<<< orphan*/  AD9523_EEPROM_ERROR_READBACK ; 
 int AD9523_EEPROM_ERROR_READBACK_FAIL ; 
 int EIO ; 
 int ad9523_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int ad9523_write (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ad9523_store_eeprom(struct iio_dev *indio_dev)
{
	int ret, tmp;

	ret = ad9523_write(indio_dev, AD9523_EEPROM_CTRL1,
			   AD9523_EEPROM_CTRL1_EEPROM_WRITE_PROT_DIS);
	if (ret < 0)
		return ret;
	ret = ad9523_write(indio_dev, AD9523_EEPROM_CTRL2,
			   AD9523_EEPROM_CTRL2_REG2EEPROM);
	if (ret < 0)
		return ret;

	tmp = 4;
	do {
		msleep(20);
		ret = ad9523_read(indio_dev,
				  AD9523_EEPROM_DATA_XFER_STATUS);
		if (ret < 0)
			return ret;
	} while ((ret & AD9523_EEPROM_DATA_XFER_IN_PROGRESS) && tmp--);

	ret = ad9523_write(indio_dev, AD9523_EEPROM_CTRL1, 0);
	if (ret < 0)
		return ret;

	ret = ad9523_read(indio_dev, AD9523_EEPROM_ERROR_READBACK);
	if (ret < 0)
		return ret;

	if (ret & AD9523_EEPROM_ERROR_READBACK_FAIL) {
		dev_err(&indio_dev->dev, "Verify EEPROM failed");
		ret = -EIO;
	}

	return ret;
}