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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_pkey_cache {int table_len; int /*<<< orphan*/ * table; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* ports; } ;
struct ib_device {TYPE_2__ cache; } ;
struct TYPE_3__ {struct ib_pkey_cache* pkey; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,size_t) ; 
 size_t rdma_start_port (struct ib_device*) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_get_cached_pkey(struct ib_device *device,
		       u8                port_num,
		       int               index,
		       u16              *pkey)
{
	struct ib_pkey_cache *cache;
	unsigned long flags;
	int ret = 0;

	if (!rdma_is_port_valid(device, port_num))
		return -EINVAL;

	read_lock_irqsave(&device->cache.lock, flags);

	cache = device->cache.ports[port_num - rdma_start_port(device)].pkey;

	if (index < 0 || index >= cache->table_len)
		ret = -EINVAL;
	else
		*pkey = cache->table[index];

	read_unlock_irqrestore(&device->cache.lock, flags);

	return ret;
}