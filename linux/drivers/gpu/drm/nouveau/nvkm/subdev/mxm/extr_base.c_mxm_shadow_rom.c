#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_mxm {int* mxms; TYPE_1__ subdev; } ;
struct nvkm_i2c_bus {int dummy; } ;
struct nvkm_i2c {int dummy; } ;
struct nvkm_device {struct nvkm_i2c* i2c; struct nvkm_bios* bios; } ;
struct nvkm_bios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mxm_ddc_map (struct nvkm_bios*,int) ; 
 scalar_t__ mxm_shadow_rom_fetch (struct nvkm_i2c_bus*,int,int /*<<< orphan*/ ,int,int*) ; 
 int mxms_headerlen (struct nvkm_mxm*) ; 
 int mxms_structlen (struct nvkm_mxm*) ; 
 struct nvkm_i2c_bus* nvkm_i2c_bus_find (struct nvkm_i2c*,int) ; 

__attribute__((used)) static bool
mxm_shadow_rom(struct nvkm_mxm *mxm, u8 version)
{
	struct nvkm_device *device = mxm->subdev.device;
	struct nvkm_bios *bios = device->bios;
	struct nvkm_i2c *i2c = device->i2c;
	struct nvkm_i2c_bus *bus = NULL;
	u8 i2cidx, mxms[6], addr, size;

	i2cidx = mxm_ddc_map(bios, 1 /* LVDS_DDC */) & 0x0f;
	if (i2cidx < 0x0f)
		bus = nvkm_i2c_bus_find(i2c, i2cidx);
	if (!bus)
		return false;

	addr = 0x54;
	if (!mxm_shadow_rom_fetch(bus, addr, 0, 6, mxms)) {
		addr = 0x56;
		if (!mxm_shadow_rom_fetch(bus, addr, 0, 6, mxms))
			return false;
	}

	mxm->mxms = mxms;
	size = mxms_headerlen(mxm) + mxms_structlen(mxm);
	mxm->mxms = kmalloc(size, GFP_KERNEL);

	if (mxm->mxms &&
	    mxm_shadow_rom_fetch(bus, addr, 0, size, mxm->mxms))
		return true;

	kfree(mxm->mxms);
	mxm->mxms = NULL;
	return false;
}