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
union power_supply_propval {int intval; } ;
struct lp8788_charger {struct iio_channel** chan; } ;
struct iio_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t LP8788_BATT_TEMP ; 
 int iio_read_channel_processed (struct iio_channel*,int*) ; 

__attribute__((used)) static int lp8788_get_battery_temperature(struct lp8788_charger *pchg,
				union power_supply_propval *val)
{
	struct iio_channel *channel = pchg->chan[LP8788_BATT_TEMP];
	int result;
	int ret;

	if (!channel)
		return -EINVAL;

	ret = iio_read_channel_processed(channel, &result);
	if (ret < 0)
		return -EINVAL;

	/* unit: 0.1 'C */
	val->intval = result * 10;

	return 0;
}