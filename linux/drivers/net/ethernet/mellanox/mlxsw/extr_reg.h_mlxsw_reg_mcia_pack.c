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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_ZERO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcia ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_device_address_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_i2c_device_address_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_l_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_module_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_page_number_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_mcia_size_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_mcia_pack(char *payload, u8 module, u8 lock,
				       u8 page_number, u16 device_addr,
				       u8 size, u8 i2c_device_addr)
{
	MLXSW_REG_ZERO(mcia, payload);
	mlxsw_reg_mcia_module_set(payload, module);
	mlxsw_reg_mcia_l_set(payload, lock);
	mlxsw_reg_mcia_page_number_set(payload, page_number);
	mlxsw_reg_mcia_device_address_set(payload, device_addr);
	mlxsw_reg_mcia_size_set(payload, size);
	mlxsw_reg_mcia_i2c_device_address_set(payload, i2c_device_addr);
}