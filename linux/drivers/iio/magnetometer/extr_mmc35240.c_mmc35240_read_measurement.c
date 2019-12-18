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
struct mmc35240_data {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  MMC35240_REG_XOUT_L ; 
 int mmc35240_take_measurement (struct mmc35240_data*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mmc35240_read_measurement(struct mmc35240_data *data, __le16 buf[3])
{
	int ret;

	ret = mmc35240_take_measurement(data);
	if (ret < 0)
		return ret;

	return regmap_bulk_read(data->regmap, MMC35240_REG_XOUT_L, (u8 *)buf,
				3 * sizeof(__le16));
}