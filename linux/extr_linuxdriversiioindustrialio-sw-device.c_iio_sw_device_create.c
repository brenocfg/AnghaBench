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
struct iio_sw_device_type {int /*<<< orphan*/  owner; TYPE_1__* ops; } ;
struct iio_sw_device {struct iio_sw_device_type* device_type; } ;
struct TYPE_2__ {struct iio_sw_device* (* probe ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct iio_sw_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct iio_sw_device*) ; 
 struct iio_sw_device_type* iio_get_sw_device_type (char const*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 struct iio_sw_device* stub1 (char const*) ; 

struct iio_sw_device *iio_sw_device_create(const char *type, const char *name)
{
	struct iio_sw_device *d;
	struct iio_sw_device_type *dt;

	dt = iio_get_sw_device_type(type);
	if (!dt) {
		pr_err("Invalid device type: %s\n", type);
		return ERR_PTR(-EINVAL);
	}
	d = dt->ops->probe(name);
	if (IS_ERR(d))
		goto out_module_put;

	d->device_type = dt;

	return d;
out_module_put:
	module_put(dt->owner);
	return d;
}