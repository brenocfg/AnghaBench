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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct apds990x_chip {int /*<<< orphan*/  lux_thres_hi; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int apds990x_set_lux_thresh (struct apds990x_chip*,int /*<<< orphan*/ *,char const*) ; 
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t apds990x_lux_thresh_above_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct apds990x_chip *chip =  dev_get_drvdata(dev);
	int ret = apds990x_set_lux_thresh(chip, &chip->lux_thres_hi, buf);

	if (ret < 0)
		return ret;
	return len;
}