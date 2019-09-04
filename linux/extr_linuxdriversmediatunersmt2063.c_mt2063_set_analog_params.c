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
struct TYPE_2__ {int f_LO2_Step; int f_out; int f_out_bw; } ;
struct mt2063_state {int frequency; TYPE_1__ AS_Data; int /*<<< orphan*/  init; } ;
struct dvb_frontend {struct mt2063_state* tuner_priv; } ;
struct analog_parameters {int mode; int std; int frequency; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int MT2063_CABLE_ANALOG ; 
 int MT2063_OFFAIR_ANALOG ; 
 int MT2063_SetReceiverMode (struct mt2063_state*,int) ; 
 int MT2063_Tune (struct mt2063_state*,int) ; 
 int V4L2_STD_MN ; 
 int V4L2_STD_PAL_G ; 
#define  V4L2_TUNER_ANALOG_TV 129 
#define  V4L2_TUNER_RADIO 128 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int mt2063_init (struct dvb_frontend*) ; 

__attribute__((used)) static int mt2063_set_analog_params(struct dvb_frontend *fe,
				    struct analog_parameters *params)
{
	struct mt2063_state *state = fe->tuner_priv;
	s32 pict_car;
	s32 pict2chanb_vsb;
	s32 ch_bw;
	s32 if_mid;
	s32 rcvr_mode;
	int status;

	dprintk(2, "\n");

	if (!state->init) {
		status = mt2063_init(fe);
		if (status < 0)
			return status;
	}

	switch (params->mode) {
	case V4L2_TUNER_RADIO:
		pict_car = 38900000;
		ch_bw = 8000000;
		pict2chanb_vsb = -(ch_bw / 2);
		rcvr_mode = MT2063_OFFAIR_ANALOG;
		break;
	case V4L2_TUNER_ANALOG_TV:
		rcvr_mode = MT2063_CABLE_ANALOG;
		if (params->std & ~V4L2_STD_MN) {
			pict_car = 38900000;
			ch_bw = 6000000;
			pict2chanb_vsb = -1250000;
		} else if (params->std & V4L2_STD_PAL_G) {
			pict_car = 38900000;
			ch_bw = 7000000;
			pict2chanb_vsb = -1250000;
		} else {		/* PAL/SECAM standards */
			pict_car = 38900000;
			ch_bw = 8000000;
			pict2chanb_vsb = -1250000;
		}
		break;
	default:
		return -EINVAL;
	}
	if_mid = pict_car - (pict2chanb_vsb + (ch_bw / 2));

	state->AS_Data.f_LO2_Step = 125000;	/* FIXME: probably 5000 for FM */
	state->AS_Data.f_out = if_mid;
	state->AS_Data.f_out_bw = ch_bw + 750000;
	status = MT2063_SetReceiverMode(state, rcvr_mode);
	if (status < 0)
		return status;

	dprintk(1, "Tuning to frequency: %d, bandwidth %d, foffset %d\n",
		params->frequency, ch_bw, pict2chanb_vsb);

	status = MT2063_Tune(state, (params->frequency + (pict2chanb_vsb + (ch_bw / 2))));
	if (status < 0)
		return status;

	state->frequency = params->frequency;
	return 0;
}