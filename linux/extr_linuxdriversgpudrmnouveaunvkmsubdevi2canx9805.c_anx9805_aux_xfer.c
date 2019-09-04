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
typedef  int u32 ;
struct nvkm_i2c_aux {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct anx9805_pad {int /*<<< orphan*/  addr; TYPE_1__* bus; } ;
struct anx9805_aux {int /*<<< orphan*/  base; int /*<<< orphan*/  addr; struct anx9805_pad* pad; } ;
struct TYPE_2__ {struct i2c_adapter i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DBG (int /*<<< orphan*/ *,char*,...) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 struct anx9805_aux* anx9805_aux (struct nvkm_i2c_aux*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int nvkm_rdi2cr (struct i2c_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wri2cr (struct i2c_adapter*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
anx9805_aux_xfer(struct nvkm_i2c_aux *base, bool retry,
		 u8 type, u32 addr, u8 *data, u8 *size)
{
	struct anx9805_aux *aux = anx9805_aux(base);
	struct anx9805_pad *pad = aux->pad;
	struct i2c_adapter *adap = &pad->bus->i2c;
	int i, ret = -ETIMEDOUT;
	u8 buf[16] = {};
	u8 tmp;

	AUX_DBG(&aux->base, "%02x %05x %d", type, addr, *size);

	tmp = nvkm_rdi2cr(adap, pad->addr, 0x07) & ~0x04;
	nvkm_wri2cr(adap, pad->addr, 0x07, tmp | 0x04);
	nvkm_wri2cr(adap, pad->addr, 0x07, tmp);
	nvkm_wri2cr(adap, pad->addr, 0xf7, 0x01);

	nvkm_wri2cr(adap, aux->addr, 0xe4, 0x80);
	if (!(type & 1)) {
		memcpy(buf, data, *size);
		AUX_DBG(&aux->base, "%16ph", buf);
		for (i = 0; i < *size; i++)
			nvkm_wri2cr(adap, aux->addr, 0xf0 + i, buf[i]);
	}
	nvkm_wri2cr(adap, aux->addr, 0xe5, ((*size - 1) << 4) | type);
	nvkm_wri2cr(adap, aux->addr, 0xe6, (addr & 0x000ff) >>  0);
	nvkm_wri2cr(adap, aux->addr, 0xe7, (addr & 0x0ff00) >>  8);
	nvkm_wri2cr(adap, aux->addr, 0xe8, (addr & 0xf0000) >> 16);
	nvkm_wri2cr(adap, aux->addr, 0xe9, 0x01);

	i = 0;
	while ((tmp = nvkm_rdi2cr(adap, aux->addr, 0xe9)) & 0x01) {
		mdelay(5);
		if (i++ == 32)
			goto done;
	}

	if ((tmp = nvkm_rdi2cr(adap, pad->addr, 0xf7)) & 0x01) {
		ret = -EIO;
		goto done;
	}

	if (type & 1) {
		for (i = 0; i < *size; i++)
			buf[i] = nvkm_rdi2cr(adap, aux->addr, 0xf0 + i);
		AUX_DBG(&aux->base, "%16ph", buf);
		memcpy(data, buf, *size);
	}

	ret = 0;
done:
	nvkm_wri2cr(adap, pad->addr, 0xf7, 0x01);
	return ret;
}