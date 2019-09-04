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
struct ib_port_attr {int pkey_tbl_len; int table_len; int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  state; int /*<<< orphan*/  lmc; scalar_t__ table; int /*<<< orphan*/  gid_tbl_len; } ;
struct ib_pkey_cache {int pkey_tbl_len; int table_len; int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  state; int /*<<< orphan*/  lmc; scalar_t__ table; int /*<<< orphan*/  gid_tbl_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* ports; } ;
struct ib_device {TYPE_2__ cache; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  port_state; int /*<<< orphan*/  lmc; struct ib_port_attr* pkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int config_non_roce_gid_cache (struct ib_device*,size_t,int /*<<< orphan*/ ) ; 
 int ib_query_pkey (struct ib_device*,size_t,int,scalar_t__) ; 
 int ib_query_port (struct ib_device*,size_t,struct ib_port_attr*) ; 
 int /*<<< orphan*/  ib_security_cache_change (struct ib_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_port_attr*) ; 
 struct ib_port_attr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rdma_is_port_valid (struct ib_device*,size_t) ; 
 int /*<<< orphan*/  rdma_protocol_roce (struct ib_device*,size_t) ; 
 size_t rdma_start_port (struct ib_device*) ; 
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
		pr_warn("ib_query_port failed (%d) for %s\n",
			ret, device->name);
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
			pr_warn("ib_query_pkey failed (%d) for %s (index %d)\n",
				ret, device->name, i);
			goto err;
		}
	}

	write_lock_irq(&device->cache.lock);

	old_pkey_cache = device->cache.ports[port -
		rdma_start_port(device)].pkey;

	device->cache.ports[port - rdma_start_port(device)].pkey = pkey_cache;
	device->cache.ports[port - rdma_start_port(device)].lmc = tprops->lmc;
	device->cache.ports[port - rdma_start_port(device)].port_state =
		tprops->state;

	device->cache.ports[port - rdma_start_port(device)].subnet_prefix =
							tprops->subnet_prefix;
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