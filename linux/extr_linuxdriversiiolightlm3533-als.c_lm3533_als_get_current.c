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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int lm3533_als_get_target (struct iio_dev*,unsigned int,int,int*) ; 
 int lm3533_als_get_zone (struct iio_dev*,int*) ; 

__attribute__((used)) static int lm3533_als_get_current(struct iio_dev *indio_dev, unsigned channel,
								int *val)
{
	u8 zone;
	u8 target;
	int ret;

	ret = lm3533_als_get_zone(indio_dev, &zone);
	if (ret)
		return ret;

	ret = lm3533_als_get_target(indio_dev, channel, zone, &target);
	if (ret)
		return ret;

	*val = target;

	return 0;
}