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
struct host1x_device {int registered; int /*<<< orphan*/  dev; } ;
struct host1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void host1x_device_del(struct host1x *host1x,
			      struct host1x_device *device)
{
	if (device->registered) {
		device->registered = false;
		device_del(&device->dev);
	}

	put_device(&device->dev);
}