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
struct apds990x_chip {int prox_continuous_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  reporting_modes ; 
 int sysfs_match_string (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static ssize_t apds990x_prox_reporting_mode_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct apds990x_chip *chip =  dev_get_drvdata(dev);
	int ret;

	ret = sysfs_match_string(reporting_modes, buf);
	if (ret < 0)
		return ret;

	chip->prox_continuous_mode = ret;
	return len;
}