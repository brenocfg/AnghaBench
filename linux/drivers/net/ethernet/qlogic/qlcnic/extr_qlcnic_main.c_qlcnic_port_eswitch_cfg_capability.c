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
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int* extra_capability; } ;

/* Variables and functions */
 int QLCNIC_FW_CAPABILITY_2_PER_PORT_ESWITCH_CFG ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_84xx_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static bool qlcnic_port_eswitch_cfg_capability(struct qlcnic_adapter *adapter)
{
	bool ret = false;

	if (qlcnic_84xx_check(adapter)) {
		ret = true;
	} else if (qlcnic_83xx_check(adapter)) {
		if (adapter->ahw->extra_capability[0] &
		    QLCNIC_FW_CAPABILITY_2_PER_PORT_ESWITCH_CFG)
			ret = true;
		else
			ret = false;
	}

	return ret;
}