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
typedef  int /*<<< orphan*/  u32 ;
struct ib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ib_device* __ib_device_get_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lists_rwsem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct ib_device *ib_device_get_by_index(u32 index)
{
	struct ib_device *device;

	down_read(&lists_rwsem);
	device = __ib_device_get_by_index(index);
	if (device)
		get_device(&device->dev);

	up_read(&lists_rwsem);
	return device;
}