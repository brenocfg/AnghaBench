#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct rtl2830_reg_val_mask {int member_0; int member_1; int member_2; int reg; int mask; int val; } ;
struct TYPE_11__ {int len; TYPE_9__* stat; } ;
struct TYPE_19__ {int len; TYPE_7__* stat; } ;
struct TYPE_17__ {int len; TYPE_5__* stat; } ;
struct TYPE_15__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_10__ post_bit_count; TYPE_8__ post_bit_error; TYPE_6__ cnr; TYPE_4__ strength; } ;
struct TYPE_12__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct rtl2830_dev {int sleeping; TYPE_2__* pdata; TYPE_1__ fe; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* demodulator_priv; } ;
struct TYPE_20__ {void* scale; } ;
struct TYPE_18__ {void* scale; } ;
struct TYPE_16__ {void* scale; } ;
struct TYPE_14__ {void* scale; } ;
struct TYPE_13__ {int vtop; int krf; int agc_targ_val; int spec_inv; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rtl2830_reg_val_mask*) ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct rtl2830_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int rtl2830_bulk_write (struct i2c_client*,int,char*,int) ; 
 int rtl2830_update_bits (struct i2c_client*,int,int,int) ; 

__attribute__((used)) static int rtl2830_init(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct rtl2830_dev *dev = i2c_get_clientdata(client);
	struct dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	int ret, i;
	struct rtl2830_reg_val_mask tab[] = {
		{0x00d, 0x01, 0x03},
		{0x00d, 0x10, 0x10},
		{0x104, 0x00, 0x1e},
		{0x105, 0x80, 0x80},
		{0x110, 0x02, 0x03},
		{0x110, 0x08, 0x0c},
		{0x17b, 0x00, 0x40},
		{0x17d, 0x05, 0x0f},
		{0x17d, 0x50, 0xf0},
		{0x18c, 0x08, 0x0f},
		{0x18d, 0x00, 0xc0},
		{0x188, 0x05, 0x0f},
		{0x189, 0x00, 0xfc},
		{0x2d5, 0x02, 0x02},
		{0x2f1, 0x02, 0x06},
		{0x2f1, 0x20, 0xf8},
		{0x16d, 0x00, 0x01},
		{0x1a6, 0x00, 0x80},
		{0x106, dev->pdata->vtop, 0x3f},
		{0x107, dev->pdata->krf, 0x3f},
		{0x112, 0x28, 0xff},
		{0x103, dev->pdata->agc_targ_val, 0xff},
		{0x00a, 0x02, 0x07},
		{0x140, 0x0c, 0x3c},
		{0x140, 0x40, 0xc0},
		{0x15b, 0x05, 0x07},
		{0x15b, 0x28, 0x38},
		{0x15c, 0x05, 0x07},
		{0x15c, 0x28, 0x38},
		{0x115, dev->pdata->spec_inv, 0x01},
		{0x16f, 0x01, 0x07},
		{0x170, 0x18, 0x38},
		{0x172, 0x0f, 0x0f},
		{0x173, 0x08, 0x38},
		{0x175, 0x01, 0x07},
		{0x176, 0x00, 0xc0},
	};

	for (i = 0; i < ARRAY_SIZE(tab); i++) {
		ret = rtl2830_update_bits(client, tab[i].reg, tab[i].mask,
					  tab[i].val);
		if (ret)
			goto err;
	}

	ret = rtl2830_bulk_write(client, 0x18f, "\x28\x00", 2);
	if (ret)
		goto err;

	ret = rtl2830_bulk_write(client, 0x195,
				 "\x04\x06\x0a\x12\x0a\x12\x1e\x28", 8);
	if (ret)
		goto err;

	/* TODO: spec init */

	/* soft reset */
	ret = rtl2830_update_bits(client, 0x101, 0x04, 0x04);
	if (ret)
		goto err;

	ret = rtl2830_update_bits(client, 0x101, 0x04, 0x00);
	if (ret)
		goto err;

	/* init stats here in order signal app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	dev->sleeping = false;

	return ret;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}