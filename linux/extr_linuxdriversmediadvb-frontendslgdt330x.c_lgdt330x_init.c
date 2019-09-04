#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int demod_chip; int /*<<< orphan*/  clock_polarity_flip; } ;
struct lgdt330x_state {scalar_t__ last_stats_time; TYPE_2__* client; TYPE_1__ config; } ;
struct TYPE_16__ {int len; TYPE_7__* stat; } ;
struct TYPE_14__ {int len; TYPE_5__* stat; } ;
struct TYPE_12__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_8__ block_count; TYPE_6__ block_error; TYPE_4__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct lgdt330x_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  lgdt3303_init_data ;
typedef  int /*<<< orphan*/  lgdt3302_init_data ;
typedef  int /*<<< orphan*/  flip_2_lgdt3303_init_data ;
typedef  int /*<<< orphan*/  flip_1_lgdt3303_init_data ;
struct TYPE_15__ {void* scale; } ;
struct TYPE_13__ {void* scale; } ;
struct TYPE_11__ {void* scale; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AGC_DELAY0 143 
#define  AGC_DELAY2 142 
#define  AGC_FUNC_CTRL2 141 
#define  AGC_FUNC_CTRL3 140 
#define  AGC_LOOP_BANDWIDTH0 139 
#define  AGC_LOOP_BANDWIDTH1 138 
#define  AGC_RF_BANDWIDTH0 137 
#define  AGC_RF_BANDWIDTH1 136 
#define  AGC_RF_BANDWIDTH2 135 
#define  DEMUX_CONTROL 134 
 int ENODEV ; 
 void* FE_SCALE_NOT_AVAILABLE ; 
#define  LGDT3302 133 
#define  LGDT3303 132 
#define  VSB_CARRIER_FREQ0 131 
#define  VSB_CARRIER_FREQ1 130 
#define  VSB_CARRIER_FREQ2 129 
#define  VSB_CARRIER_FREQ3 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dprintk (struct lgdt330x_state*,char*,char*) ; 
 int i2c_write_demod_bytes (struct lgdt330x_state*,int const*,int) ; 
 int lgdt330x_sw_reset (struct lgdt330x_state*) ; 

__attribute__((used)) static int lgdt330x_init(struct dvb_frontend *fe)
{
	struct lgdt330x_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	char  *chip_name;
	int    err;
	/*
	 * Array of byte pairs <address, value>
	 * to initialize each different chip
	 */
	static const u8 lgdt3302_init_data[] = {
		/* Use 50MHz param values from spec sheet since xtal is 50 */
		/*
		 * Change the value of NCOCTFV[25:0] of carrier
		 * recovery center frequency register
		 */
		VSB_CARRIER_FREQ0, 0x00,
		VSB_CARRIER_FREQ1, 0x87,
		VSB_CARRIER_FREQ2, 0x8e,
		VSB_CARRIER_FREQ3, 0x01,
		/*
		 * Change the TPCLK pin polarity
		 * data is valid on falling clock
		 */
		DEMUX_CONTROL, 0xfb,
		/*
		 * Change the value of IFBW[11:0] of
		 * AGC IF/RF loop filter bandwidth register
		 */
		AGC_RF_BANDWIDTH0, 0x40,
		AGC_RF_BANDWIDTH1, 0x93,
		AGC_RF_BANDWIDTH2, 0x00,
		/*
		 * Change the value of bit 6, 'nINAGCBY' and
		 * 'NSSEL[1:0] of ACG function control register 2
		 */
		AGC_FUNC_CTRL2, 0xc6,
		/*
		 * Change the value of bit 6 'RFFIX'
		 * of AGC function control register 3
		 */
		AGC_FUNC_CTRL3, 0x40,
		/*
		 * Set the value of 'INLVTHD' register 0x2a/0x2c
		 * to 0x7fe
		 */
		AGC_DELAY0, 0x07,
		AGC_DELAY2, 0xfe,
		/*
		 * Change the value of IAGCBW[15:8]
		 * of inner AGC loop filter bandwidth
		 */
		AGC_LOOP_BANDWIDTH0, 0x08,
		AGC_LOOP_BANDWIDTH1, 0x9a
	};
	static const u8 lgdt3303_init_data[] = {
		0x4c, 0x14
	};
	static const u8 flip_1_lgdt3303_init_data[] = {
		0x4c, 0x14,
		0x87, 0xf3
	};
	static const u8 flip_2_lgdt3303_init_data[] = {
		0x4c, 0x14,
		0x87, 0xda
	};

	/*
	 * Hardware reset is done using gpio[0] of cx23880x chip.
	 * I'd like to do it here, but don't know how to find chip address.
	 * cx88-cards.c arranges for the reset bit to be inactive (high).
	 * Maybe there needs to be a callable function in cx88-core or
	 * the caller of this function needs to do it.
	 */

	switch (state->config.demod_chip) {
	case LGDT3302:
		chip_name = "LGDT3302";
		err = i2c_write_demod_bytes(state, lgdt3302_init_data,
					    sizeof(lgdt3302_init_data));
		break;
	case LGDT3303:
		chip_name = "LGDT3303";
		switch (state->config.clock_polarity_flip) {
		case 2:
			err = i2c_write_demod_bytes(state,
						    flip_2_lgdt3303_init_data,
						    sizeof(flip_2_lgdt3303_init_data));
			break;
		case 1:
			err = i2c_write_demod_bytes(state,
						    flip_1_lgdt3303_init_data,
						    sizeof(flip_1_lgdt3303_init_data));
			break;
		case 0:
		default:
			err = i2c_write_demod_bytes(state, lgdt3303_init_data,
						    sizeof(lgdt3303_init_data));
		}
		break;
	default:
		chip_name = "undefined";
		dev_warn(&state->client->dev,
			 "Only LGDT3302 and LGDT3303 are supported chips.\n");
		err = -ENODEV;
	}
	dprintk(state, "Initialized the %s chip\n", chip_name);
	if (err < 0)
		return err;

	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.len = 1;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_count.len = 1;
	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	state->last_stats_time = 0;

	return lgdt330x_sw_reset(state);
}