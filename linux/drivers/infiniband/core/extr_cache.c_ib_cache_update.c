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
struct ib_port_attr {int pkey_tbl_len; int table_len; int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  state; int /*<<< orphan*/  lmc; scalar_t__ table; int /*<<< orphan*/  gid_tbl_len; } ;
struct ib_pkey_cache {int pkey_tbl_len; int table_len; int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  state; int /*<<< orphan*/  lmc; scalar_t__ table; int /*<<< orphan*/  gid_tbl_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct ib_device {TYPE_3__ cache; TYPE_2__* port_data; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  port_state; int /*<<< orphan*/  lmc; struct ib_port_attr* pkey; } ;
struct TYPE_5__ {TYPE_1__ cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int config_non_roce_gid_cache (struct ib_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int ib_query_pkey (struct ib_device*,size_t,int,scalar_t__) ; 
 int ib_query_port (struct ib_device*,size_t,struct ib_port_attr*) ; 
 int /*<<< orphan*/  ib_security_cache_change (struct ib_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_port_attr*) ; 
 struct ib_port_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,size_t) ; 
 int /*<<< orphan*/  rdma_protocol_roce (struct ib_device*,size_t) ; 
 int struct_size (struct ib_port_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  table ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_cache_update(struct ib_device *device,
			    u8                port,
			    bool	      enforce_security)
{
	struct ib_port_attr       *tprops = NULL;
	struct ib_pkey_cache      *pkey_cache = NULL, *old_pkey_cache;
	int                        i;
	int                        ret;

	if (!rdma_is_port_valid(device, port))
		return;

	tprops = kmalloc(sizeof *tprops, GFP_KERNEL);
	if (!tprops)
		return;

	ret = ib_query_port(device, port, tprops);
	if (ret) {
		dev_warn(&device->dev, "ib_query_port failed (%d)\n", ret);
		goto err;
	}

	if (!rdma_protocol_roce(device, port)) {
		ret = config_non_roce_gid_cache(device, port,
						tprops->gid_tbl_len);
		if (ret)
			goto err;
	}

	pkey_cache = kmalloc(struct_size(pkey_cache, table,
					 tprops->pkey_tbl_len),
			     GFP_KERNEL);
	if (!pkey_cache)
		goto err;

	pkey_cache->table_len = tprops->pkey_tbl_len;

	for (i = 0; i < pkey_cache->table_len; ++i) {
		ret = ib_query_pkey(device, port, i, pkey_cache->table + i);
		if (ret) {
			dev_warn(&device->dev,
				 "ib_query_pkey failed (%d) for index %d\n",
				 ret, i);
			goto err;
		}
	}

	write_lock_irq(&device->cache.lock);

	old_pkey_cache = device->port_data[port].cache.pkey;

	device->port_data[port].cache.pkey = pkey_cache;
	device->port_data[port].cache.lmc = tprops->lmc;
	device->port_data[port].cache.port_state = tprops->state;

	device->port_data[port].cache.subnet_prefix = tprops->subnet_prefix;
	write_unlock_irq(&device->cache.lock);

	if (enforce_security)
		ib_security_cache_change(device,
					 port,
					 tprops->subnet_prefix);

	kfree(old_pkey_cache);
	kfree(tprops);
	return;

err:
	kfree(pkey_cache);
	kfree(tprops);
}