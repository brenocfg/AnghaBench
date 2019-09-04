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
struct raw_device_data {struct block_device* binding; } ;
struct block_device {int /*<<< orphan*/  bd_dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int max_raw_minors ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct raw_device_data* raw_devices ; 
 int /*<<< orphan*/  raw_mutex ; 

__attribute__((used)) static int bind_get(int number, dev_t *dev)
{
	struct raw_device_data *rawdev;
	struct block_device *bdev;

	if (number <= 0 || number >= max_raw_minors)
		return -EINVAL;

	rawdev = &raw_devices[number];

	mutex_lock(&raw_mutex);
	bdev = rawdev->binding;
	*dev = bdev ? bdev->bd_dev : 0;
	mutex_unlock(&raw_mutex);
	return 0;
}