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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int jitterDelay; } ;
struct aiptek {TYPE_1__ newSetting; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct aiptek* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int,int*) ; 

__attribute__((used)) static ssize_t
store_tabletJitterDelay(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);
	int err, j;

	err = kstrtoint(buf, 10, &j);
	if (err)
		return err;

	aiptek->newSetting.jitterDelay = j;
	return count;
}