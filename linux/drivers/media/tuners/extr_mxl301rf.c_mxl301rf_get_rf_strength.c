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
typedef  int u16 ;
struct mxl301rf_state {int dummy; } ;
struct dtv_fe_stats {int len; TYPE_2__* stat; } ;
struct TYPE_3__ {struct dtv_fe_stats strength; } ;
struct dvb_frontend {struct mxl301rf_state* tuner_priv; TYPE_1__ dtv_property_cache; } ;
typedef  int s64 ;
struct TYPE_4__ {int svalue; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_SCALE_DECIBEL ; 
 int /*<<< orphan*/  FE_SCALE_NOT_AVAILABLE ; 
 int reg_read (struct mxl301rf_state*,int,int*) ; 
 int reg_write (struct mxl301rf_state*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mxl301rf_get_rf_strength(struct dvb_frontend *fe, u16 *out)
{
	struct mxl301rf_state *state;
	int ret;
	u8  rf_in1, rf_in2, rf_off1, rf_off2;
	u16 rf_in, rf_off;
	s64 level;
	struct dtv_fe_stats *rssi;

	rssi = &fe->dtv_property_cache.strength;
	rssi->len = 1;
	rssi->stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	*out = 0;

	state = fe->tuner_priv;
	ret = reg_write(state, 0x14, 0x01);
	if (ret < 0)
		return ret;
	usleep_range(1000, 2000);

	ret = reg_read(state, 0x18, &rf_in1);
	if (ret == 0)
		ret = reg_read(state, 0x19, &rf_in2);
	if (ret == 0)
		ret = reg_read(state, 0xd6, &rf_off1);
	if (ret == 0)
		ret = reg_read(state, 0xd7, &rf_off2);
	if (ret != 0)
		return ret;

	rf_in = (rf_in2 & 0x07) << 8 | rf_in1;
	rf_off = (rf_off2 & 0x0f) << 5 | (rf_off1 >> 3);
	level = rf_in - rf_off - (113 << 3); /* x8 dBm */
	level = level * 1000 / 8;
	rssi->stat[0].svalue = level;
	rssi->stat[0].scale = FE_SCALE_DECIBEL;
	/* *out = (level - min) * 100 / (max - min) */
	*out = (rf_in - rf_off + (1 << 9) - 1) * 100 / ((5 << 9) - 2);
	return 0;
}