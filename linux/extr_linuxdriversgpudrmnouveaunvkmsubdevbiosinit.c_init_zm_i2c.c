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
typedef  size_t u8 ;
struct nvkm_bios {int dummy; } ;
struct nvbios_init {scalar_t__ offset; TYPE_2__* subdev; } ;
struct i2c_msg {size_t addr; size_t len; size_t* buf; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {struct nvkm_bios* bios; } ;

/* Variables and functions */
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 struct i2c_adapter* init_i2c (struct nvbios_init*,size_t) ; 
 int nvbios_rd08 (struct nvkm_bios*,scalar_t__) ; 
 int /*<<< orphan*/  trace (char*,size_t,...) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static void
init_zm_i2c(struct nvbios_init *init)
{
	struct nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_rd08(bios, init->offset + 3);
	u8 data[256], i;

	trace("ZM_I2C\tI2C[0x%02x][0x%02x]\n", index, addr);
	init->offset += 4;

	for (i = 0; i < count; i++) {
		data[i] = nvbios_rd08(bios, init->offset);
		trace("\t0x%02x\n", data[i]);
		init->offset++;
	}

	if (init_exec(init)) {
		struct i2c_adapter *adap = init_i2c(init, index);
		struct i2c_msg msg = {
			.addr = addr, .flags = 0, .len = count, .buf = data,
		};
		int ret;

		if (adap && (ret = i2c_transfer(adap, &msg, 1)) != 1)
			warn("i2c wr failed, %d\n", ret);
	}
}