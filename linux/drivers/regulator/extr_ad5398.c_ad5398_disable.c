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
struct regulator_dev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct ad5398_chip_info {struct i2c_client* client; } ;

/* Variables and functions */
 unsigned short AD5398_CURRENT_EN_MASK ; 
 int ad5398_read_reg (struct i2c_client*,unsigned short*) ; 
 int ad5398_write_reg (struct i2c_client*,unsigned short) ; 
 struct ad5398_chip_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int ad5398_disable(struct regulator_dev *rdev)
{
	struct ad5398_chip_info *chip = rdev_get_drvdata(rdev);
	struct i2c_client *client = chip->client;
	unsigned short data;
	int ret;

	ret = ad5398_read_reg(client, &data);
	if (ret < 0)
		return ret;

	if (!(data & AD5398_CURRENT_EN_MASK))
		return 0;

	data &= ~AD5398_CURRENT_EN_MASK;

	ret = ad5398_write_reg(client, data);

	return ret;
}