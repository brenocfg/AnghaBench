#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct i2c_msg {int addr; int len; int* buf; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  init_exec_set (struct nvbios_init*,int) ; 
 struct i2c_adapter* init_i2c (struct nvbios_init*,int) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static void
init_i2c_long_if(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2) >> 1;
	u8 reglo = nvbios_rd08(bios, init->offset + 3);
	u8 reghi = nvbios_rd08(bios, init->offset + 4);
	u8  mask = nvbios_rd08(bios, init->offset + 5);
	u8  data = nvbios_rd08(bios, init->offset + 6);
	struct i2c_adapter *adap;

	trace("I2C_LONG_IF\t"
	      "I2C[0x%02x][0x%02x][0x%02x%02x] & 0x%02x == 0x%02x\n",
	      index, addr, reglo, reghi, mask, data);
	init->offset += 7;

	adap = init_i2c(init, index);
	if (adap) {
		u8 i[2] = { reghi, reglo };
		u8 o[1] = {};
		struct i2c_msg msg[] = {
			{ .addr = addr, .flags = 0, .len = 2, .buf = i },
			{ .addr = addr, .flags = I2C_M_RD, .len = 1, .buf = o }
		};
		int ret;

		ret = i2c_transfer(adap, msg, 2);
		if (ret == 2 && ((o[0] & mask) == data))
			return;
	}

	init_exec_set(init, false);
}