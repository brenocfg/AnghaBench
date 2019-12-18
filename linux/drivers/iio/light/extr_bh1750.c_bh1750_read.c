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
struct bh1750_data {unsigned long mtreg; int /*<<< orphan*/  client; struct bh1750_chip_info* chip_info; } ;
struct bh1750_chip_info {unsigned long mtreg_to_usec; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BH1750_ONE_TIME_H_RES_MODE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static int bh1750_read(struct bh1750_data *data, int *val)
{
	int ret;
	__be16 result;
	const struct bh1750_chip_info *chip_info = data->chip_info;
	unsigned long delay = chip_info->mtreg_to_usec * data->mtreg;

	/*
	 * BH1721 will enter continuous mode on receiving this command.
	 * Note, that this eliminates need for bh1750_resume().
	 */
	ret = i2c_smbus_write_byte(data->client, BH1750_ONE_TIME_H_RES_MODE);
	if (ret < 0)
		return ret;

	usleep_range(delay + 15000, delay + 40000);

	ret = i2c_master_recv(data->client, (char *)&result, 2);
	if (ret < 0)
		return ret;

	*val = be16_to_cpu(result);

	return 0;
}