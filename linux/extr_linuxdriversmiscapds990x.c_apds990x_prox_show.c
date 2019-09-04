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
struct apds990x_chip {int prox_data; int /*<<< orphan*/  mutex; int /*<<< orphan*/  prox_en; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct apds990x_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t apds990x_prox_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	ssize_t ret;
	struct apds990x_chip *chip =  dev_get_drvdata(dev);

	if (pm_runtime_suspended(dev) || !chip->prox_en)
		return -EIO;

	mutex_lock(&chip->mutex);
	ret = sprintf(buf, "%d\n", chip->prox_data);
	mutex_unlock(&chip->mutex);
	return ret;
}