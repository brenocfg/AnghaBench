#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int als_cal_target; } ;
struct tsl2772_chip {TYPE_1__ settings; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct tsl2772_chip* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t in_illuminance0_target_input_show(struct device *dev,
						 struct device_attribute *attr,
						 char *buf)
{
	struct tsl2772_chip *chip = iio_priv(dev_to_iio_dev(dev));

	return snprintf(buf, PAGE_SIZE, "%d\n", chip->settings.als_cal_target);
}