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
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct iio_sw_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iio_sw_device*) ; 

void iio_sw_device_destroy(struct iio_sw_device *d)
{
	struct iio_sw_device_type *dt = d->device_type;

	dt->ops->remove(d);
	module_put(dt->owner);
}