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
struct imon_context {int rf_isassociating; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENODEV ; 
 struct imon_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_associate_24g (struct imon_context*) ; 

__attribute__((used)) static ssize_t store_associate_remote(struct device *d,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct imon_context *ictx;

	ictx = dev_get_drvdata(d);

	if (!ictx)
		return -ENODEV;

	mutex_lock(&ictx->lock);
	ictx->rf_isassociating = true;
	send_associate_24g(ictx);
	mutex_unlock(&ictx->lock);

	return count;
}