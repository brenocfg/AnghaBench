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
typedef  enum mlxsw_reg_mgpir_device_type { ____Placeholder_mlxsw_reg_mgpir_device_type } mlxsw_reg_mgpir_device_type ;

/* Variables and functions */
 int mlxsw_reg_mgpir_device_type_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpir_devices_per_flash_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpir_num_of_devices_get (char*) ; 

__attribute__((used)) static inline void
mlxsw_reg_mgpir_unpack(char *payload, u8 *num_of_devices,
		       enum mlxsw_reg_mgpir_device_type *device_type,
		       u8 *devices_per_flash)
{
	if (num_of_devices)
		*num_of_devices = mlxsw_reg_mgpir_num_of_devices_get(payload);
	if (device_type)
		*device_type = mlxsw_reg_mgpir_device_type_get(payload);
	if (devices_per_flash)
		*devices_per_flash =
				mlxsw_reg_mgpir_devices_per_flash_get(payload);
}