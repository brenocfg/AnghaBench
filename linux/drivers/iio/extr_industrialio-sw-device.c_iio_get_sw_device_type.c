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
struct iio_sw_device_type {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 struct iio_sw_device_type* __iio_find_sw_device_type (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_types_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
struct iio_sw_device_type *iio_get_sw_device_type(const char *name)
{
	struct iio_sw_device_type *dt;

	mutex_lock(&iio_device_types_lock);
	dt = __iio_find_sw_device_type(name, strlen(name));
	if (dt && !try_module_get(dt->owner))
		dt = NULL;
	mutex_unlock(&iio_device_types_lock);

	return dt;
}