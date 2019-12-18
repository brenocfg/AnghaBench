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
struct imon_context {int /*<<< orphan*/  lock; scalar_t__ rf_isassociating; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct imon_context* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strscpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_associate_remote(struct device *d,
				     struct device_attribute *attr,
				     char *buf)
{
	struct imon_context *ictx = dev_get_drvdata(d);

	if (!ictx)
		return -ENODEV;

	mutex_lock(&ictx->lock);
	if (ictx->rf_isassociating)
		strscpy(buf, "associating\n", PAGE_SIZE);
	else
		strscpy(buf, "closed\n", PAGE_SIZE);

	dev_info(d, "Visit http://www.lirc.org/html/imon-24g.html for instructions on how to associate your iMON 2.4G DT/LT remote\n");
	mutex_unlock(&ictx->lock);
	return strlen(buf);
}