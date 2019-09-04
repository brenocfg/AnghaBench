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
struct bh1770_chip {int prox_data; int /*<<< orphan*/  mutex; scalar_t__ prox_enable_count; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct bh1770_chip* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t bh1770_prox_result_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct bh1770_chip *chip =  dev_get_drvdata(dev);
	ssize_t ret;

	mutex_lock(&chip->mutex);
	if (chip->prox_enable_count && !pm_runtime_suspended(dev))
		ret = sprintf(buf, "%d\n", chip->prox_data);
	else
		ret = -EIO;
	mutex_unlock(&chip->mutex);
	return ret;
}