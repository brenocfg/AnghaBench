#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct nvkm_i2c_aux {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_9__ {TYPE_3__* pad; } ;
struct g94_i2c_aux {int ch; TYPE_4__ base; } ;
struct TYPE_8__ {TYPE_2__* i2c; } ;
struct TYPE_6__ {struct nvkm_device* device; } ;
struct TYPE_7__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_ERR (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  AUX_TRACE (TYPE_4__*,char*,...) ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 struct g94_i2c_aux* g94_i2c_aux (struct nvkm_i2c_aux*) ; 
 int /*<<< orphan*/  g94_i2c_aux_fini (struct g94_i2c_aux*) ; 
 int g94_i2c_aux_init (struct g94_i2c_aux*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int nvkm_mask (struct nvkm_device*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvkm_rd32 (struct nvkm_device*,int const) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int const,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
g94_i2c_aux_xfer(struct nvkm_i2c_aux *obj, bool retry,
		 u8 type, u32 addr, u8 *data, u8 *size)
{
	struct g94_i2c_aux *aux = g94_i2c_aux(obj);
	struct nvkm_device *device = aux->base.pad->i2c->subdev.device;
	const u32 base = aux->ch * 0x50;
	u32 ctrl, stat, timeout, retries = 0;
	u32 xbuf[4] = {};
	int ret, i;

	AUX_TRACE(&aux->base, "%d: %08x %d", type, addr, *size);

	ret = g94_i2c_aux_init(aux);
	if (ret < 0)
		goto out;

	stat = nvkm_rd32(device, 0x00e4e8 + base);
	if (!(stat & 0x10000000)) {
		AUX_TRACE(&aux->base, "sink not detected");
		ret = -ENXIO;
		goto out;
	}

	if (!(type & 1)) {
		memcpy(xbuf, data, *size);
		for (i = 0; i < 16; i += 4) {
			AUX_TRACE(&aux->base, "wr %08x", xbuf[i / 4]);
			nvkm_wr32(device, 0x00e4c0 + base + i, xbuf[i / 4]);
		}
	}

	ctrl  = nvkm_rd32(device, 0x00e4e4 + base);
	ctrl &= ~0x0001f1ff;
	ctrl |= type << 12;
	ctrl |= (*size ? (*size - 1) : 0x00000100);
	nvkm_wr32(device, 0x00e4e0 + base, addr);

	/* (maybe) retry transaction a number of times on failure... */
	do {
		/* reset, and delay a while if this is a retry */
		nvkm_wr32(device, 0x00e4e4 + base, 0x80000000 | ctrl);
		nvkm_wr32(device, 0x00e4e4 + base, 0x00000000 | ctrl);
		if (retries)
			udelay(400);

		/* transaction request, wait up to 1ms for it to complete */
		nvkm_wr32(device, 0x00e4e4 + base, 0x00010000 | ctrl);

		timeout = 1000;
		do {
			ctrl = nvkm_rd32(device, 0x00e4e4 + base);
			udelay(1);
			if (!timeout--) {
				AUX_ERR(&aux->base, "timeout %08x", ctrl);
				ret = -EIO;
				goto out;
			}
		} while (ctrl & 0x00010000);
		ret = 0;

		/* read status, and check if transaction completed ok */
		stat = nvkm_mask(device, 0x00e4e8 + base, 0, 0);
		if ((stat & 0x000f0000) == 0x00080000 ||
		    (stat & 0x000f0000) == 0x00020000)
			ret = 1;
		if ((stat & 0x00000100))
			ret = -ETIMEDOUT;
		if ((stat & 0x00000e00))
			ret = -EIO;

		AUX_TRACE(&aux->base, "%02d %08x %08x", retries, ctrl, stat);
	} while (ret && retry && retries++ < 32);

	if (type & 1) {
		for (i = 0; i < 16; i += 4) {
			xbuf[i / 4] = nvkm_rd32(device, 0x00e4d0 + base + i);
			AUX_TRACE(&aux->base, "rd %08x", xbuf[i / 4]);
		}
		memcpy(data, xbuf, *size);
		*size = stat & 0x0000001f;
	}

out:
	g94_i2c_aux_fini(aux);
	return ret < 0 ? ret : (stat & 0x000f0000) >> 16;
}