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
struct si1133_data {int /*<<< orphan*/  regmap; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int SI1133_PART_ID ; 
 int /*<<< orphan*/  SI1133_REG_MFR_ID ; 
 int /*<<< orphan*/  SI1133_REG_PART_ID ; 
 int /*<<< orphan*/  SI1133_REG_REV_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int,unsigned int) ; 
 struct si1133_data* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int si1133_validate_ids(struct iio_dev *iio_dev)
{
	struct si1133_data *data = iio_priv(iio_dev);

	unsigned int part_id, rev_id, mfr_id;
	int err;

	err = regmap_read(data->regmap, SI1133_REG_PART_ID, &part_id);
	if (err)
		return err;

	err = regmap_read(data->regmap, SI1133_REG_REV_ID, &rev_id);
	if (err)
		return err;

	err = regmap_read(data->regmap, SI1133_REG_MFR_ID, &mfr_id);
	if (err)
		return err;

	dev_info(&iio_dev->dev,
		 "Device ID part %#02hhx rev %#02hhx mfr %#02hhx\n",
		 part_id, rev_id, mfr_id);
	if (part_id != SI1133_PART_ID) {
		dev_err(&iio_dev->dev,
			"Part ID mismatch got %#02hhx, expected %#02x\n",
			part_id, SI1133_PART_ID);
		return -ENODEV;
	}

	return 0;
}