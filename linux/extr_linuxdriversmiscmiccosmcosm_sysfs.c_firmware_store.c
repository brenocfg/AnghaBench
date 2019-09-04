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
struct cosm_device {char* firmware; int /*<<< orphan*/  cosm_mutex; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cosm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static ssize_t
firmware_store(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct cosm_device *cdev = dev_get_drvdata(dev);

	if (!cdev)
		return -EINVAL;

	mutex_lock(&cdev->cosm_mutex);
	kfree(cdev->firmware);

	cdev->firmware = kmalloc(count + 1, GFP_KERNEL);
	if (!cdev->firmware) {
		count = -ENOMEM;
		goto unlock;
	}
	strncpy(cdev->firmware, buf, count);

	if (cdev->firmware[count - 1] == '\n')
		cdev->firmware[count - 1] = '\0';
	else
		cdev->firmware[count] = '\0';
unlock:
	mutex_unlock(&cdev->cosm_mutex);
	return count;
}