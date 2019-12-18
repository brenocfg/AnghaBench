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
struct net {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  devices_rwsem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_device_try_get (struct ib_device*) ; 
 int /*<<< orphan*/  rdma_dev_access_netns (struct ib_device*,struct net const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct ib_device* xa_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct ib_device *ib_device_get_by_index(const struct net *net, u32 index)
{
	struct ib_device *device;

	down_read(&devices_rwsem);
	device = xa_load(&devices, index);
	if (device) {
		if (!rdma_dev_access_netns(device, net)) {
			device = NULL;
			goto out;
		}

		if (!ib_device_try_get(device))
			device = NULL;
	}
out:
	up_read(&devices_rwsem);
	return device;
}