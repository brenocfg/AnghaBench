#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int u32 ;
struct lme2510_state {int tuner_config; int signal_level; int signal_sn; scalar_t__ i2c_talk_onoff; } ;
struct dvb_usb_adapter {struct dvb_frontend** fe; } ;
struct TYPE_15__ {int len; TYPE_11__* stat; } ;
struct TYPE_13__ {int len; TYPE_9__* stat; } ;
struct TYPE_23__ {int len; TYPE_7__* stat; } ;
struct TYPE_21__ {int len; TYPE_5__* stat; } ;
struct TYPE_19__ {int len; TYPE_3__* stat; } ;
struct TYPE_17__ {int len; TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_12__ cnr; TYPE_10__ strength; TYPE_8__ post_bit_error; TYPE_6__ post_bit_count; TYPE_4__ block_error; TYPE_2__ block_count; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_24__ {void* uvalue; void* scale; } ;
struct TYPE_22__ {void* scale; } ;
struct TYPE_20__ {void* scale; } ;
struct TYPE_18__ {void* scale; } ;
struct TYPE_16__ {void* scale; } ;
struct TYPE_14__ {void* uvalue; void* scale; } ;

/* Variables and functions */
 void* FE_SCALE_NOT_AVAILABLE ; 
 void* FE_SCALE_RELATIVE ; 
#define  TUNER_LG 131 
#define  TUNER_RS2000 130 
#define  TUNER_S0194 129 
#define  TUNER_S7395 128 
 struct lme2510_state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int reg_to_16bits (int) ; 

__attribute__((used)) static void lme2510_update_stats(struct dvb_usb_adapter *adap)
{
	struct lme2510_state *st = adap_to_priv(adap);
	struct dvb_frontend *fe = adap->fe[0];
	struct dtv_frontend_properties *c;
	u32 s_tmp = 0, c_tmp = 0;

	if (!fe)
		return;

	c = &fe->dtv_property_cache;

	c->block_count.len = 1;
	c->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->block_error.len = 1;
	c->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	if (st->i2c_talk_onoff) {
		c->strength.len = 1;
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->cnr.len = 1;
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		return;
	}

	switch (st->tuner_config) {
	case TUNER_LG:
		s_tmp = reg_to_16bits(0xff - st->signal_level);
		c_tmp = reg_to_16bits(0xff - st->signal_sn);
		break;
	case TUNER_S7395:
	case TUNER_S0194:
		s_tmp = 0xffff - (((st->signal_level * 2) << 8) * 5 / 4);
		c_tmp = reg_to_16bits((0xff - st->signal_sn - 0xa1) * 3);
		break;
	case TUNER_RS2000:
		s_tmp = reg_to_16bits(st->signal_level);
		c_tmp = reg_to_16bits(st->signal_sn);
	}

	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_RELATIVE;
	c->strength.stat[0].uvalue = (u64)s_tmp;

	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_RELATIVE;
	c->cnr.stat[0].uvalue = (u64)c_tmp;
}