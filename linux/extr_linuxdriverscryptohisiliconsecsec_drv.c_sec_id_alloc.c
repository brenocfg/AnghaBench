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
struct sec_dev_info {int sec_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SEC_MAX_DEVICES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sec_dev_info** sec_devices ; 
 int /*<<< orphan*/  sec_id_lock ; 

__attribute__((used)) static int sec_id_alloc(struct sec_dev_info *info)
{
	int ret = 0;
	int i;

	mutex_lock(&sec_id_lock);

	for (i = 0; i < SEC_MAX_DEVICES; i++)
		if (!sec_devices[i])
			break;
	if (i == SEC_MAX_DEVICES) {
		ret = -ENOMEM;
		goto unlock;
	}
	info->sec_id = i;
	sec_devices[info->sec_id] = info;

unlock:
	mutex_unlock(&sec_id_lock);

	return ret;
}