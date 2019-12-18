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
struct visor_device {int /*<<< orphan*/  device; scalar_t__ pending_msg_hdr; int /*<<< orphan*/  list_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLVM_DEVICE_DESTROY ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visorbus_response (struct visor_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void remove_visor_device(struct visor_device *dev)
{
	list_del(&dev->list_all);
	put_device(&dev->device);
	if (dev->pending_msg_hdr)
		visorbus_response(dev, 0, CONTROLVM_DEVICE_DESTROY);
	device_unregister(&dev->device);
}