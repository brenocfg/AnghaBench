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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum pm_reg_name { ____Placeholder_pm_reg_name } pm_reg_name ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_WO_MMIO (int const,int /*<<< orphan*/ ) ; 
#define  debug_bus_control 135 
#define  ext_tr_timer 134 
#define  group_control 133 
#define  pm_control 132 
#define  pm_interval 131 
#define  pm_start_stop 130 
#define  pm_status 129 
#define  trace_address 128 

void cbe_write_pm(u32 cpu, enum pm_reg_name reg, u32 val)
{
	switch (reg) {
	case group_control:
		WRITE_WO_MMIO(group_control, val);
		break;

	case debug_bus_control:
		WRITE_WO_MMIO(debug_bus_control, val);
		break;

	case trace_address:
		WRITE_WO_MMIO(trace_address, val);
		break;

	case ext_tr_timer:
		WRITE_WO_MMIO(ext_tr_timer, val);
		break;

	case pm_status:
		WRITE_WO_MMIO(pm_status, val);
		break;

	case pm_control:
		WRITE_WO_MMIO(pm_control, val);
		break;

	case pm_interval:
		WRITE_WO_MMIO(pm_interval, val);
		break;

	case pm_start_stop:
		WRITE_WO_MMIO(pm_start_stop, val);
		break;
	}
}