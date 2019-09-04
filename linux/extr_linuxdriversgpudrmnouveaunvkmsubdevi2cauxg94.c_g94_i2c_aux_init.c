#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct TYPE_8__ {TYPE_3__* pad; } ;
struct g94_i2c_aux {int ch; TYPE_4__ base; } ;
struct TYPE_7__ {TYPE_2__* i2c; } ;
struct TYPE_5__ {struct nvkm_device* device; } ;
struct TYPE_6__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_ERR (TYPE_4__*,char*,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  g94_i2c_aux_fini (struct g94_i2c_aux*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int const) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
g94_i2c_aux_init(struct g94_i2c_aux *aux)
{
	struct nvkm_device *device = aux->base.pad->i2c->subdev.device;
	const u32 unksel = 1; /* nfi which to use, or if it matters.. */
	const u32 ureq = unksel ? 0x00100000 : 0x00200000;
	const u32 urep = unksel ? 0x01000000 : 0x02000000;
	u32 ctrl, timeout;

	/* wait up to 1ms for any previous transaction to be done... */
	timeout = 1000;
	do {
		ctrl = nvkm_rd32(device, 0x00e4e4 + (aux->ch * 0x50));
		udelay(1);
		if (!timeout--) {
			AUX_ERR(&aux->base, "begin idle timeout %08x", ctrl);
			return -EBUSY;
		}
	} while (ctrl & 0x03010000);

	/* set some magic, and wait up to 1ms for it to appear */
	nvkm_mask(device, 0x00e4e4 + (aux->ch * 0x50), 0x00300000, ureq);
	timeout = 1000;
	do {
		ctrl = nvkm_rd32(device, 0x00e4e4 + (aux->ch * 0x50));
		udelay(1);
		if (!timeout--) {
			AUX_ERR(&aux->base, "magic wait %08x", ctrl);
			g94_i2c_aux_fini(aux);
			return -EBUSY;
		}
	} while ((ctrl & 0x03000000) != urep);

	return 0;
}