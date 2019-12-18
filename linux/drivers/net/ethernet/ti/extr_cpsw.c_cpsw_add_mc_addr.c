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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct addr_sync_ctx {int consumed; scalar_t__ flush; struct net_device* ndev; int /*<<< orphan*/  const* addr; } ;

/* Variables and functions */
 int cpsw_set_mc (struct net_device*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  cpsw_update_vlan_mc ; 
 int vlan_for_each (struct net_device*,int /*<<< orphan*/ ,struct addr_sync_ctx*) ; 

__attribute__((used)) static int cpsw_add_mc_addr(struct net_device *ndev, const u8 *addr, int num)
{
	struct addr_sync_ctx sync_ctx;
	int ret;

	sync_ctx.consumed = 0;
	sync_ctx.addr = addr;
	sync_ctx.ndev = ndev;
	sync_ctx.flush = 0;

	ret = vlan_for_each(ndev, cpsw_update_vlan_mc, &sync_ctx);
	if (sync_ctx.consumed < num && !ret)
		ret = cpsw_set_mc(ndev, addr, -1, 1);

	return ret;
}