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
struct nvkm_i2c_aux {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct anx9805_pad {TYPE_1__* bus; } ;
struct anx9805_aux {int /*<<< orphan*/  base; int /*<<< orphan*/  addr; struct anx9805_pad* pad; } ;
struct TYPE_2__ {struct i2c_adapter i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DBG (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  AUX_ERR (int /*<<< orphan*/ *,char*) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 struct anx9805_aux* anx9805_aux (struct nvkm_i2c_aux*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int nvkm_rdi2cr (struct i2c_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wri2cr (struct i2c_adapter*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
anx9805_aux_lnk_ctl(struct nvkm_i2c_aux *base,
		    int link_nr, int link_bw, bool enh)
{
	struct anx9805_aux *aux = anx9805_aux(base);
	struct anx9805_pad *pad = aux->pad;
	struct i2c_adapter *adap = &pad->bus->i2c;
	u8 tmp, i;

	AUX_DBG(&aux->base, "ANX9805 train %d %02x %d",
		link_nr, link_bw, enh);

	nvkm_wri2cr(adap, aux->addr, 0xa0, link_bw);
	nvkm_wri2cr(adap, aux->addr, 0xa1, link_nr | (enh ? 0x80 : 0x00));
	nvkm_wri2cr(adap, aux->addr, 0xa2, 0x01);
	nvkm_wri2cr(adap, aux->addr, 0xa8, 0x01);

	i = 0;
	while ((tmp = nvkm_rdi2cr(adap, aux->addr, 0xa8)) & 0x01) {
		mdelay(5);
		if (i++ == 100) {
			AUX_ERR(&aux->base, "link training timeout");
			return -ETIMEDOUT;
		}
	}

	if (tmp & 0x70) {
		AUX_ERR(&aux->base, "link training failed");
		return -EIO;
	}

	return 0;
}