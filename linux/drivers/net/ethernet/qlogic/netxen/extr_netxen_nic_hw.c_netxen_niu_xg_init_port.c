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
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {TYPE_1__ ahw; } ;

/* Variables and functions */
 scalar_t__ NETXEN_NIU_XGE_CONFIG_0 ; 
 scalar_t__ NETXEN_NIU_XGE_CONFIG_1 ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,scalar_t__,int) ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netxen_niu_xg_init_port(struct netxen_adapter *adapter, int port)
{
	if (NX_IS_REVISION_P2(adapter->ahw.revision_id)) {
		NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_1+(0x10000*port), 0x1447);
		NXWR32(adapter, NETXEN_NIU_XGE_CONFIG_0+(0x10000*port), 0x5);
	}

	return 0;
}