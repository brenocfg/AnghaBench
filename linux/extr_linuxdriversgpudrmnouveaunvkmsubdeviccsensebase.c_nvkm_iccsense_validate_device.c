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
struct i2c_adapter {int dummy; } ;
typedef  enum nvbios_extdev_type { ____Placeholder_nvbios_extdev_type } nvbios_extdev_type ;

/* Variables and functions */
#define  NVBIOS_EXTDEV_INA209 130 
#define  NVBIOS_EXTDEV_INA219 129 
#define  NVBIOS_EXTDEV_INA3221 128 
 int nv_rd16i2cr (struct i2c_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
nvkm_iccsense_validate_device(struct i2c_adapter *i2c, u8 addr,
			      enum nvbios_extdev_type type)
{
	switch (type) {
	case NVBIOS_EXTDEV_INA209:
	case NVBIOS_EXTDEV_INA219:
		return nv_rd16i2cr(i2c, addr, 0x0) >= 0;
	case NVBIOS_EXTDEV_INA3221:
		return nv_rd16i2cr(i2c, addr, 0xff) == 0x3220 &&
		       nv_rd16i2cr(i2c, addr, 0xfe) == 0x5449;
	default:
		return false;
	}
}