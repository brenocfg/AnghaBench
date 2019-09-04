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
struct iio_sw_device {int dummy; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  iio_sw_device_destroy (struct iio_sw_device*) ; 
 struct iio_sw_device* to_iio_sw_device (struct config_item*) ; 

__attribute__((used)) static void device_drop_group(struct config_group *group,
			      struct config_item *item)
{
	struct iio_sw_device *d = to_iio_sw_device(item);

	iio_sw_device_destroy(d);
	config_item_put(item);
}