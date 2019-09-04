#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {int physical_port; TYPE_1__ ahw; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int NETXEN_NIU_MAX_XG_PORTS ; 
 scalar_t__ NETXEN_NIU_XGE_CONFIG_0 ; 
 scalar_t__ NXWR32 (struct netxen_adapter*,scalar_t__,scalar_t__) ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netxen_niu_disable_xg_port(struct netxen_adapter *adapter)
{
	__u32 mac_cfg;
	u32 port = adapter->physical_port;

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		return 0;

	if (port >= NETXEN_NIU_MAX_XG_PORTS)
		return -EINVAL;

	mac_cfg = 0;
	if (NXWR32(adapter,
			NETXEN_NIU_XGE_CONFIG_0 + (0x10000 * port), mac_cfg))
		return -EIO;
	return 0;
}