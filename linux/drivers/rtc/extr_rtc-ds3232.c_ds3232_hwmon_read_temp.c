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
typedef  int u8 ;
typedef  int /*<<< orphan*/  temp_buf ;
struct ds3232 {int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  DS3232_REG_TEMPERATURE ; 
 struct ds3232* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ds3232_hwmon_read_temp(struct device *dev, long int *mC)
{
	struct ds3232 *ds3232 = dev_get_drvdata(dev);
	u8 temp_buf[2];
	s16 temp;
	int ret;

	ret = regmap_bulk_read(ds3232->regmap, DS3232_REG_TEMPERATURE, temp_buf,
			       sizeof(temp_buf));
	if (ret < 0)
		return ret;

	/*
	 * Temperature is represented as a 10-bit code with a resolution of
	 * 0.25 degree celsius and encoded in two's complement format.
	 */
	temp = (temp_buf[0] << 8) | temp_buf[1];
	temp >>= 6;
	*mC = temp * 250;

	return 0;
}