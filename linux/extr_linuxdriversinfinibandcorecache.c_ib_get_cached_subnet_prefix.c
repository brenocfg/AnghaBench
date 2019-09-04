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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* ports; } ;
struct ib_device {TYPE_2__ cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  subnet_prefix; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,int) ; 
 int rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_get_cached_subnet_prefix(struct ib_device *device,
				u8                port_num,
				u64              *sn_pfx)
{
	unsigned long flags;
	int p;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	p = port_num - rdma_start_port(device);
	read_lock_irqsave(&device->cache.lock, flags);
	*sn_pfx = device->cache.ports[p].subnet_prefix;
	read_unlock_irqrestore(&device->cache.lock, flags);

	return 0;
}