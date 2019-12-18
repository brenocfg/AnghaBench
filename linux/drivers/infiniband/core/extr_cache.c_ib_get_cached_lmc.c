#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct ib_device {TYPE_3__ cache; TYPE_2__* port_data; } ;
struct TYPE_4__ {size_t lmc; } ;
struct TYPE_5__ {TYPE_1__ cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,size_t) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_get_cached_lmc(struct ib_device *device,
		      u8                port_num,
		      u8                *lmc)
{
	unsigned long flags;
	int ret = 0;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);
	*lmc = device->port_data[port_num].cache.lmc;
	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}