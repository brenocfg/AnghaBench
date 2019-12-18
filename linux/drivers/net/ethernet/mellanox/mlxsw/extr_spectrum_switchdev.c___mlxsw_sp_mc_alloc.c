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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_mid {int in_hw; struct mlxsw_sp_mid* ports_in_mid; int /*<<< orphan*/  list; int /*<<< orphan*/  fid; int /*<<< orphan*/  addr; } ;
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  mids_list; int /*<<< orphan*/  multicast_enabled; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mid*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_mc_write_mdb_entry (struct mlxsw_sp*,struct mlxsw_sp_mid*,struct mlxsw_sp_bridge_device*) ; 

__attribute__((used)) static struct
mlxsw_sp_mid *__mlxsw_sp_mc_alloc(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_bridge_device *bridge_device,
				  const unsigned char *addr,
				  u16 fid)
{
	struct mlxsw_sp_mid *mid;
	size_t alloc_size;

	mid = kzalloc(sizeof(*mid), GFP_KERNEL);
	if (!mid)
		return NULL;

	alloc_size = sizeof(unsigned long) *
		     BITS_TO_LONGS(mlxsw_core_max_ports(mlxsw_sp->core));

	mid->ports_in_mid = kzalloc(alloc_size, GFP_KERNEL);
	if (!mid->ports_in_mid)
		goto err_ports_in_mid_alloc;

	ether_addr_copy(mid->addr, addr);
	mid->fid = fid;
	mid->in_hw = false;

	if (!bridge_device->multicast_enabled)
		goto out;

	if (!mlxsw_sp_mc_write_mdb_entry(mlxsw_sp, mid, bridge_device))
		goto err_write_mdb_entry;

out:
	list_add_tail(&mid->list, &bridge_device->mids_list);
	return mid;

err_write_mdb_entry:
	kfree(mid->ports_in_mid);
err_ports_in_mid_alloc:
	kfree(mid);
	return NULL;
}