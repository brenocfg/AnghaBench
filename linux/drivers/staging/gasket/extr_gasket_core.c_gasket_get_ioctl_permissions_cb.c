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
struct gasket_dev {TYPE_2__* internal_desc; } ;
typedef  int /*<<< orphan*/  gasket_ioctl_permissions_cb_t ;
struct TYPE_4__ {TYPE_1__* driver_desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioctl_permissions_cb; } ;

/* Variables and functions */

gasket_ioctl_permissions_cb_t
gasket_get_ioctl_permissions_cb(struct gasket_dev *gasket_dev)
{
	return gasket_dev->internal_desc->driver_desc->ioctl_permissions_cb;
}