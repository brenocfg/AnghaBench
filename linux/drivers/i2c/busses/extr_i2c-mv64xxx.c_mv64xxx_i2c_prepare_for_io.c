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
typedef  int u32 ;
struct mv64xxx_i2c_data {int cntl_bits; int addr1; int addr2; } ;
struct i2c_msg {int flags; scalar_t__ addr; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int I2C_M_TEN ; 
 int MV64XXX_I2C_ADDR_ADDR (int) ; 
 int MV64XXX_I2C_REG_CONTROL_ACK ; 
 int MV64XXX_I2C_REG_CONTROL_INTEN ; 
 int MV64XXX_I2C_REG_CONTROL_TWSIEN ; 

__attribute__((used)) static void
mv64xxx_i2c_prepare_for_io(struct mv64xxx_i2c_data *drv_data,
	struct i2c_msg *msg)
{
	u32	dir = 0;

	drv_data->cntl_bits = MV64XXX_I2C_REG_CONTROL_ACK |
		MV64XXX_I2C_REG_CONTROL_INTEN | MV64XXX_I2C_REG_CONTROL_TWSIEN;

	if (msg->flags & I2C_M_RD)
		dir = 1;

	if (msg->flags & I2C_M_TEN) {
		drv_data->addr1 = 0xf0 | (((u32)msg->addr & 0x300) >> 7) | dir;
		drv_data->addr2 = (u32)msg->addr & 0xff;
	} else {
		drv_data->addr1 = MV64XXX_I2C_ADDR_ADDR((u32)msg->addr) | dir;
		drv_data->addr2 = 0;
	}
}