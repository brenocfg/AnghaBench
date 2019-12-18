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
typedef  enum port_module_event_error_type { ____Placeholder_port_module_event_error_type } port_module_event_error_type ;

/* Variables and functions */
#define  MLX5_MODULE_EVENT_ERROR_BAD_CABLE 136 
#define  MLX5_MODULE_EVENT_ERROR_BUS_STUCK 135 
#define  MLX5_MODULE_EVENT_ERROR_ENFORCE_PART_NUMBER_LIST 134 
#define  MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE 133 
#define  MLX5_MODULE_EVENT_ERROR_LONG_RANGE_FOR_NON_MLNX 132 
#define  MLX5_MODULE_EVENT_ERROR_NO_EEPROM_RETRY_TIMEOUT 131 
#define  MLX5_MODULE_EVENT_ERROR_PCIE_POWER_SLOT_EXCEEDED 130 
#define  MLX5_MODULE_EVENT_ERROR_POWER_BUDGET_EXCEEDED 129 
#define  MLX5_MODULE_EVENT_ERROR_UNKNOWN_IDENTIFIER 128 

__attribute__((used)) static const char *mlx5_pme_error_to_string(enum port_module_event_error_type error)
{
	switch (error) {
	case MLX5_MODULE_EVENT_ERROR_POWER_BUDGET_EXCEEDED:
		return "Power budget exceeded";
	case MLX5_MODULE_EVENT_ERROR_LONG_RANGE_FOR_NON_MLNX:
		return "Long Range for non MLNX cable";
	case MLX5_MODULE_EVENT_ERROR_BUS_STUCK:
		return "Bus stuck (I2C or data shorted)";
	case MLX5_MODULE_EVENT_ERROR_NO_EEPROM_RETRY_TIMEOUT:
		return "No EEPROM/retry timeout";
	case MLX5_MODULE_EVENT_ERROR_ENFORCE_PART_NUMBER_LIST:
		return "Enforce part number list";
	case MLX5_MODULE_EVENT_ERROR_UNKNOWN_IDENTIFIER:
		return "Unknown identifier";
	case MLX5_MODULE_EVENT_ERROR_HIGH_TEMPERATURE:
		return "High Temperature";
	case MLX5_MODULE_EVENT_ERROR_BAD_CABLE:
		return "Bad or shorted cable/module";
	case MLX5_MODULE_EVENT_ERROR_PCIE_POWER_SLOT_EXCEEDED:
		return "One or more network ports have been powered down due to insufficient/unadvertised power on the PCIe slot";
	default:
		return "Unknown error";
	}
}