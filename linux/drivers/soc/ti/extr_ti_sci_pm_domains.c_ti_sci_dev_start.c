#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* get_device_exclusive ) (struct ti_sci_handle const*,int) ;int (* get_device ) (struct ti_sci_handle const*,int) ;} ;
struct TYPE_4__ {TYPE_1__ dev_ops; } ;
struct ti_sci_handle {TYPE_2__ ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_ti_sci_dev_exclusive (struct device*) ; 
 int stub1 (struct ti_sci_handle const*,int) ; 
 int stub2 (struct ti_sci_handle const*,int) ; 
 int ti_sci_dev_id (struct device*) ; 
 struct ti_sci_handle* ti_sci_dev_to_sci_handle (struct device*) ; 

__attribute__((used)) static int ti_sci_dev_start(struct device *dev)
{
	const struct ti_sci_handle *ti_sci = ti_sci_dev_to_sci_handle(dev);
	int idx = ti_sci_dev_id(dev);

	if (is_ti_sci_dev_exclusive(dev))
		return ti_sci->ops.dev_ops.get_device_exclusive(ti_sci, idx);
	else
		return ti_sci->ops.dev_ops.get_device(ti_sci, idx);
}