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
typedef  int /*<<< orphan*/  t_buf ;
struct device {int dummy; } ;
struct bmp280_data {int /*<<< orphan*/  regmap; struct device* dev; } ;
struct bmp280_calib {int T1; int T2; int T3; int P1; int P2; int P3; int P4; int P5; int P6; int P7; int P8; int P9; unsigned int H1; unsigned int H3; void* H6; void* H5; void* H4; void* H2; } ;
typedef  int /*<<< orphan*/  p_buf ;
typedef  unsigned int __le16 ;

/* Variables and functions */
 unsigned int BME280_CHIP_ID ; 
 int BMP280_COMP_PRESS_REG_COUNT ; 
 int BMP280_COMP_TEMP_REG_COUNT ; 
 int /*<<< orphan*/  BMP280_REG_COMP_H1 ; 
 int /*<<< orphan*/  BMP280_REG_COMP_H2 ; 
 int /*<<< orphan*/  BMP280_REG_COMP_H3 ; 
 int /*<<< orphan*/  BMP280_REG_COMP_H4 ; 
 int /*<<< orphan*/  BMP280_REG_COMP_H5 ; 
 int /*<<< orphan*/  BMP280_REG_COMP_H6 ; 
 int /*<<< orphan*/  BMP280_REG_COMP_PRESS_START ; 
 int /*<<< orphan*/  BMP280_REG_COMP_TEMP_START ; 
 size_t P1 ; 
 size_t P2 ; 
 size_t P3 ; 
 size_t P4 ; 
 size_t P5 ; 
 size_t P6 ; 
 size_t P7 ; 
 size_t P8 ; 
 size_t P9 ; 
 size_t T1 ; 
 size_t T2 ; 
 size_t T3 ; 
 int /*<<< orphan*/  add_device_randomness (unsigned int*,int) ; 
 int be16_to_cpu (unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int le16_to_cpu (unsigned int) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 void* sign_extend32 (unsigned int,int) ; 

__attribute__((used)) static int bmp280_read_calib(struct bmp280_data *data,
			     struct bmp280_calib *calib,
			     unsigned int chip)
{
	int ret;
	unsigned int tmp;
	struct device *dev = data->dev;
	__le16 t_buf[BMP280_COMP_TEMP_REG_COUNT / 2];
	__le16 p_buf[BMP280_COMP_PRESS_REG_COUNT / 2];

	/* Read temperature calibration values. */
	ret = regmap_bulk_read(data->regmap, BMP280_REG_COMP_TEMP_START,
			       t_buf, BMP280_COMP_TEMP_REG_COUNT);
	if (ret < 0) {
		dev_err(data->dev,
			"failed to read temperature calibration parameters\n");
		return ret;
	}

	/* Toss the temperature calibration data into the entropy pool */
	add_device_randomness(t_buf, sizeof(t_buf));

	calib->T1 = le16_to_cpu(t_buf[T1]);
	calib->T2 = le16_to_cpu(t_buf[T2]);
	calib->T3 = le16_to_cpu(t_buf[T3]);

	/* Read pressure calibration values. */
	ret = regmap_bulk_read(data->regmap, BMP280_REG_COMP_PRESS_START,
			       p_buf, BMP280_COMP_PRESS_REG_COUNT);
	if (ret < 0) {
		dev_err(data->dev,
			"failed to read pressure calibration parameters\n");
		return ret;
	}

	/* Toss the pressure calibration data into the entropy pool */
	add_device_randomness(p_buf, sizeof(p_buf));

	calib->P1 = le16_to_cpu(p_buf[P1]);
	calib->P2 = le16_to_cpu(p_buf[P2]);
	calib->P3 = le16_to_cpu(p_buf[P3]);
	calib->P4 = le16_to_cpu(p_buf[P4]);
	calib->P5 = le16_to_cpu(p_buf[P5]);
	calib->P6 = le16_to_cpu(p_buf[P6]);
	calib->P7 = le16_to_cpu(p_buf[P7]);
	calib->P8 = le16_to_cpu(p_buf[P8]);
	calib->P9 = le16_to_cpu(p_buf[P9]);

	/*
	 * Read humidity calibration values.
	 * Due to some odd register addressing we cannot just
	 * do a big bulk read. Instead, we have to read each Hx
	 * value separately and sometimes do some bit shifting...
	 * Humidity data is only available on BME280.
	 */
	if (chip != BME280_CHIP_ID)
		return 0;

	ret = regmap_read(data->regmap, BMP280_REG_COMP_H1, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read H1 comp value\n");
		return ret;
	}
	calib->H1 = tmp;

	ret = regmap_bulk_read(data->regmap, BMP280_REG_COMP_H2, &tmp, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read H2 comp value\n");
		return ret;
	}
	calib->H2 = sign_extend32(le16_to_cpu(tmp), 15);

	ret = regmap_read(data->regmap, BMP280_REG_COMP_H3, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read H3 comp value\n");
		return ret;
	}
	calib->H3 = tmp;

	ret = regmap_bulk_read(data->regmap, BMP280_REG_COMP_H4, &tmp, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read H4 comp value\n");
		return ret;
	}
	calib->H4 = sign_extend32(((be16_to_cpu(tmp) >> 4) & 0xff0) |
				  (be16_to_cpu(tmp) & 0xf), 11);

	ret = regmap_bulk_read(data->regmap, BMP280_REG_COMP_H5, &tmp, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read H5 comp value\n");
		return ret;
	}
	calib->H5 = sign_extend32(((le16_to_cpu(tmp) >> 4) & 0xfff), 11);

	ret = regmap_read(data->regmap, BMP280_REG_COMP_H6, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read H6 comp value\n");
		return ret;
	}
	calib->H6 = sign_extend32(tmp, 7);

	return 0;
}