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
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 size_t ERESTARTSYS ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* prng_data ; 
 int /*<<< orphan*/  prng_sha512_reseed () ; 

__attribute__((used)) static ssize_t prng_reseed_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	if (mutex_lock_interruptible(&prng_data->mutex))
		return -ERESTARTSYS;
	prng_sha512_reseed();
	mutex_unlock(&prng_data->mutex);

	return count;
}