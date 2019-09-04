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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int nv_rd16i2cr (struct i2c_adapter*,int,int) ; 

__attribute__((used)) static int
nvkm_iccsense_poll_lane(struct i2c_adapter *i2c, u8 addr, u8 shunt_reg,
			u8 shunt_shift, u8 bus_reg, u8 bus_shift, u8 shunt,
			u16 lsb)
{
	int vshunt = nv_rd16i2cr(i2c, addr, shunt_reg);
	int vbus = nv_rd16i2cr(i2c, addr, bus_reg);

	if (vshunt < 0 || vbus < 0)
		return -EINVAL;

	vshunt >>= shunt_shift;
	vbus >>= bus_shift;

	return vbus * vshunt * lsb / shunt;
}