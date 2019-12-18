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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct sx8 {int started; int first_time_lock; TYPE_1__ signal_info; } ;
struct dtv_frontend_properties {int stream_id; int modulation; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct sx8* demodulator_priv; } ;

/* Variables and functions */
#define  APSK_16 129 
#define  APSK_32 128 
 int NO_STREAM_ID_FILTER ; 
 int /*<<< orphan*/  SX8_DEMOD_WAIT_SIGNAL ; 
 int SX8_TSCONFIG_MODE_IQ ; 
 int SX8_TSCONFIG_MODE_NORMAL ; 
 int SX8_TSCONFIG_TSHEADER ; 
 int start (struct dvb_frontend*,int,int,int) ; 
 int start_iq (struct dvb_frontend*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stop (struct dvb_frontend*) ; 

__attribute__((used)) static int set_parameters(struct dvb_frontend *fe)
{
	int stat = 0;
	struct sx8 *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 ts_config = SX8_TSCONFIG_MODE_NORMAL, iq_mode = 0, isi;

	if (state->started)
		stop(fe);

	isi = p->stream_id;
	if (isi != NO_STREAM_ID_FILTER)
		iq_mode = (isi & 0x30000000) >> 28;

	if (iq_mode)
		ts_config = (SX8_TSCONFIG_TSHEADER | SX8_TSCONFIG_MODE_IQ);
	if (iq_mode < 3) {
		u32 mask;

		switch (p->modulation) {
		/* uncomment whenever these modulations hit the DVB API
		 *	case APSK_256:
		 *		mask = 0x7f;
		 *		break;
		 *	case APSK_128:
		 *		mask = 0x3f;
		 *		break;
		 *	case APSK_64:
		 *		mask = 0x1f;
		 *		break;
		 */
		case APSK_32:
			mask = 0x0f;
			break;
		case APSK_16:
			mask = 0x07;
			break;
		default:
			mask = 0x03;
			break;
		}
		stat = start(fe, 3, mask, ts_config);
	} else {
		stat = start_iq(fe, 0, 4, ts_config);
	}
	if (!stat) {
		state->started = 1;
		state->first_time_lock = 1;
		state->signal_info.status = SX8_DEMOD_WAIT_SIGNAL;
	}

	return stat;
}