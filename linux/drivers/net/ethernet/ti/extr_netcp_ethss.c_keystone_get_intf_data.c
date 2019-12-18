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
struct netcp_intf {int dummy; } ;
struct gbe_intf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gbe_module ; 
 struct gbe_intf* netcp_module_get_intf_data (int /*<<< orphan*/ *,struct netcp_intf*) ; 
 int /*<<< orphan*/  xgbe_module ; 

__attribute__((used)) static struct gbe_intf *keystone_get_intf_data(struct netcp_intf *netcp)
{
	struct gbe_intf *gbe_intf;

	gbe_intf = netcp_module_get_intf_data(&gbe_module, netcp);
	if (!gbe_intf)
		gbe_intf = netcp_module_get_intf_data(&xgbe_module, netcp);

	return gbe_intf;
}