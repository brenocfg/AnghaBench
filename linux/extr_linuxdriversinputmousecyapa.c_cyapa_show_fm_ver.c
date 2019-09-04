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
struct cyapa {int /*<<< orphan*/  state_sync_lock; int /*<<< orphan*/  fw_min_ver; int /*<<< orphan*/  fw_maj_ver; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct cyapa* dev_get_drvdata (struct device*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cyapa_show_fm_ver(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	int error;
	struct cyapa *cyapa = dev_get_drvdata(dev);

	error = mutex_lock_interruptible(&cyapa->state_sync_lock);
	if (error)
		return error;
	error = scnprintf(buf, PAGE_SIZE, "%d.%d\n", cyapa->fw_maj_ver,
			 cyapa->fw_min_ver);
	mutex_unlock(&cyapa->state_sync_lock);
	return error;
}