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
typedef  int /*<<< orphan*/  u8 ;
struct device {int dummy; } ;
struct bme680_data {int /*<<< orphan*/  regmap; } ;
struct bme680_calib {unsigned int par_t3; unsigned int par_p3; unsigned int par_p6; unsigned int par_p7; unsigned int par_p10; unsigned int par_h1; unsigned int par_h2; unsigned int par_h3; unsigned int par_h4; unsigned int par_h5; unsigned int par_h6; unsigned int par_h7; unsigned int par_gh1; unsigned int par_gh3; unsigned int res_heat_val; void* range_sw_err; void* res_heat_range; void* par_gh2; void* par_p9; void* par_p8; void* par_p5; void* par_p4; void* par_p2; void* par_p1; void* par_t2; void* par_t1; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 unsigned int BME680_BIT_H1_DATA_MASK ; 
 int /*<<< orphan*/  BME680_GH1_REG ; 
 int /*<<< orphan*/  BME680_GH2_LSB_REG ; 
 int /*<<< orphan*/  BME680_GH3_REG ; 
 int /*<<< orphan*/  BME680_H1_LSB_REG ; 
 int /*<<< orphan*/  BME680_H1_MSB_REG ; 
 int /*<<< orphan*/  BME680_H2_LSB_REG ; 
 int /*<<< orphan*/  BME680_H2_MSB_REG ; 
 int /*<<< orphan*/  BME680_H3_REG ; 
 int /*<<< orphan*/  BME680_H4_REG ; 
 int /*<<< orphan*/  BME680_H5_REG ; 
 int /*<<< orphan*/  BME680_H6_REG ; 
 int /*<<< orphan*/  BME680_H7_REG ; 
 unsigned int BME680_HUM_REG_SHIFT_VAL ; 
 int /*<<< orphan*/  BME680_P10_REG ; 
 int /*<<< orphan*/  BME680_P1_LSB_REG ; 
 int /*<<< orphan*/  BME680_P2_LSB_REG ; 
 int /*<<< orphan*/  BME680_P3_REG ; 
 int /*<<< orphan*/  BME680_P4_LSB_REG ; 
 int /*<<< orphan*/  BME680_P5_LSB_REG ; 
 int /*<<< orphan*/  BME680_P6_REG ; 
 int /*<<< orphan*/  BME680_P7_REG ; 
 int /*<<< orphan*/  BME680_P8_LSB_REG ; 
 int /*<<< orphan*/  BME680_P9_LSB_REG ; 
 int /*<<< orphan*/  BME680_REG_RANGE_SW_ERR ; 
 int /*<<< orphan*/  BME680_REG_RES_HEAT_RANGE ; 
 int /*<<< orphan*/  BME680_REG_RES_HEAT_VAL ; 
 int /*<<< orphan*/  BME680_RHRANGE_MASK ; 
 int /*<<< orphan*/  BME680_RSERROR_MASK ; 
 int /*<<< orphan*/  BME680_T1_LSB_REG ; 
 int /*<<< orphan*/  BME680_T2_LSB_REG ; 
 int /*<<< orphan*/  BME680_T3_REG ; 
 void* FIELD_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int bme680_read_calib(struct bme680_data *data,
			     struct bme680_calib *calib)
{
	struct device *dev = regmap_get_device(data->regmap);
	unsigned int tmp, tmp_msb, tmp_lsb;
	int ret;
	__le16 buf;

	/* Temperature related coefficients */
	ret = regmap_bulk_read(data->regmap, BME680_T1_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_T1_LSB_REG\n");
		return ret;
	}
	calib->par_t1 = le16_to_cpu(buf);

	ret = regmap_bulk_read(data->regmap, BME680_T2_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_T2_LSB_REG\n");
		return ret;
	}
	calib->par_t2 = le16_to_cpu(buf);

	ret = regmap_read(data->regmap, BME680_T3_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_T3_REG\n");
		return ret;
	}
	calib->par_t3 = tmp;

	/* Pressure related coefficients */
	ret = regmap_bulk_read(data->regmap, BME680_P1_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P1_LSB_REG\n");
		return ret;
	}
	calib->par_p1 = le16_to_cpu(buf);

	ret = regmap_bulk_read(data->regmap, BME680_P2_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P2_LSB_REG\n");
		return ret;
	}
	calib->par_p2 = le16_to_cpu(buf);

	ret = regmap_read(data->regmap, BME680_P3_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P3_REG\n");
		return ret;
	}
	calib->par_p3 = tmp;

	ret = regmap_bulk_read(data->regmap, BME680_P4_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P4_LSB_REG\n");
		return ret;
	}
	calib->par_p4 = le16_to_cpu(buf);

	ret = regmap_bulk_read(data->regmap, BME680_P5_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P5_LSB_REG\n");
		return ret;
	}
	calib->par_p5 = le16_to_cpu(buf);

	ret = regmap_read(data->regmap, BME680_P6_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P6_REG\n");
		return ret;
	}
	calib->par_p6 = tmp;

	ret = regmap_read(data->regmap, BME680_P7_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P7_REG\n");
		return ret;
	}
	calib->par_p7 = tmp;

	ret = regmap_bulk_read(data->regmap, BME680_P8_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P8_LSB_REG\n");
		return ret;
	}
	calib->par_p8 = le16_to_cpu(buf);

	ret = regmap_bulk_read(data->regmap, BME680_P9_LSB_REG, (u8 *) &buf, 2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P9_LSB_REG\n");
		return ret;
	}
	calib->par_p9 = le16_to_cpu(buf);

	ret = regmap_read(data->regmap, BME680_P10_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_P10_REG\n");
		return ret;
	}
	calib->par_p10 = tmp;

	/* Humidity related coefficients */
	ret = regmap_read(data->regmap, BME680_H1_MSB_REG, &tmp_msb);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H1_MSB_REG\n");
		return ret;
	}
	ret = regmap_read(data->regmap, BME680_H1_LSB_REG, &tmp_lsb);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H1_LSB_REG\n");
		return ret;
	}
	calib->par_h1 = (tmp_msb << BME680_HUM_REG_SHIFT_VAL) |
			(tmp_lsb & BME680_BIT_H1_DATA_MASK);

	ret = regmap_read(data->regmap, BME680_H2_MSB_REG, &tmp_msb);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H2_MSB_REG\n");
		return ret;
	}
	ret = regmap_read(data->regmap, BME680_H2_LSB_REG, &tmp_lsb);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H2_LSB_REG\n");
		return ret;
	}
	calib->par_h2 = (tmp_msb << BME680_HUM_REG_SHIFT_VAL) |
			(tmp_lsb >> BME680_HUM_REG_SHIFT_VAL);

	ret = regmap_read(data->regmap, BME680_H3_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H3_REG\n");
		return ret;
	}
	calib->par_h3 = tmp;

	ret = regmap_read(data->regmap, BME680_H4_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H4_REG\n");
		return ret;
	}
	calib->par_h4 = tmp;

	ret = regmap_read(data->regmap, BME680_H5_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H5_REG\n");
		return ret;
	}
	calib->par_h5 = tmp;

	ret = regmap_read(data->regmap, BME680_H6_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H6_REG\n");
		return ret;
	}
	calib->par_h6 = tmp;

	ret = regmap_read(data->regmap, BME680_H7_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_H7_REG\n");
		return ret;
	}
	calib->par_h7 = tmp;

	/* Gas heater related coefficients */
	ret = regmap_read(data->regmap, BME680_GH1_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_GH1_REG\n");
		return ret;
	}
	calib->par_gh1 = tmp;

	ret = regmap_bulk_read(data->regmap, BME680_GH2_LSB_REG, (u8 *) &buf,
			       2);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_GH2_LSB_REG\n");
		return ret;
	}
	calib->par_gh2 = le16_to_cpu(buf);

	ret = regmap_read(data->regmap, BME680_GH3_REG, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read BME680_GH3_REG\n");
		return ret;
	}
	calib->par_gh3 = tmp;

	/* Other coefficients */
	ret = regmap_read(data->regmap, BME680_REG_RES_HEAT_RANGE, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read resistance heat range\n");
		return ret;
	}
	calib->res_heat_range = FIELD_GET(BME680_RHRANGE_MASK, tmp);

	ret = regmap_read(data->regmap, BME680_REG_RES_HEAT_VAL, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read resistance heat value\n");
		return ret;
	}
	calib->res_heat_val = tmp;

	ret = regmap_read(data->regmap, BME680_REG_RANGE_SW_ERR, &tmp);
	if (ret < 0) {
		dev_err(dev, "failed to read range software error\n");
		return ret;
	}
	calib->range_sw_err = FIELD_GET(BME680_RSERROR_MASK, tmp);

	return 0;
}