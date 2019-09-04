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
struct sht21 {int /*<<< orphan*/  lock; int /*<<< orphan*/ * eic; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct sht21* dev_get_drvdata (struct device*) ; 
 int eic_read (struct sht21*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t eic_show(struct device *dev,
	struct device_attribute *attr,
	char *buf)
{
	struct sht21 *sht21 = dev_get_drvdata(dev);
	int ret;

	ret = sizeof(sht21->eic) - 1;
	mutex_lock(&sht21->lock);
	if (!sht21->eic[0])
		ret = eic_read(sht21);
	if (ret > 0)
		memcpy(buf, sht21->eic, ret);
	mutex_unlock(&sht21->lock);
	return ret;
}