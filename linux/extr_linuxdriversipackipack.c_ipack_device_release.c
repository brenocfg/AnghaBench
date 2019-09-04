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
struct ipack_device {int /*<<< orphan*/  (* release ) (struct ipack_device*) ;int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ipack_device*) ; 
 struct ipack_device* to_ipack_dev (struct device*) ; 

__attribute__((used)) static void ipack_device_release(struct device *dev)
{
	struct ipack_device *device = to_ipack_dev(dev);
	kfree(device->id);
	device->release(device);
}