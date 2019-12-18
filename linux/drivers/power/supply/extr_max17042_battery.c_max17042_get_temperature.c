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
typedef  int /*<<< orphan*/  u32 ;
struct regmap {int dummy; } ;
struct max17042_chip {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_TEMP ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max17042_get_temperature(struct max17042_chip *chip, int *temp)
{
	int ret;
	u32 data;
	struct regmap *map = chip->regmap;

	ret = regmap_read(map, MAX17042_TEMP, &data);
	if (ret < 0)
		return ret;

	*temp = sign_extend32(data, 15);
	/* The value is converted into deci-centigrade scale */
	/* Units of LSB = 1 / 256 degree Celsius */
	*temp = *temp * 10 / 256;
	return 0;
}