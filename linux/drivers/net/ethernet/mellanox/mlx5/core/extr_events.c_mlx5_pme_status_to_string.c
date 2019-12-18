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
typedef  enum port_module_event_status_type { ____Placeholder_port_module_event_status_type } port_module_event_status_type ;

/* Variables and functions */
#define  MLX5_MODULE_STATUS_DISABLED 131 
#define  MLX5_MODULE_STATUS_ERROR 130 
#define  MLX5_MODULE_STATUS_PLUGGED 129 
#define  MLX5_MODULE_STATUS_UNPLUGGED 128 

__attribute__((used)) static const char *mlx5_pme_status_to_string(enum port_module_event_status_type status)
{
	switch (status) {
	case MLX5_MODULE_STATUS_PLUGGED:
		return "Cable plugged";
	case MLX5_MODULE_STATUS_UNPLUGGED:
		return "Cable unplugged";
	case MLX5_MODULE_STATUS_ERROR:
		return "Cable error";
	case MLX5_MODULE_STATUS_DISABLED:
		return "Cable disabled";
	default:
		return "Unknown status";
	}
}