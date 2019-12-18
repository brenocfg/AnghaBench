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
struct gasket_driver_desc {int dummy; } ;
struct gasket_dev {TYPE_1__* internal_desc; } ;
struct TYPE_2__ {struct gasket_driver_desc const* driver_desc; } ;

/* Variables and functions */

const struct gasket_driver_desc *gasket_get_driver_desc(struct gasket_dev *dev)
{
	return dev->internal_desc->driver_desc;
}