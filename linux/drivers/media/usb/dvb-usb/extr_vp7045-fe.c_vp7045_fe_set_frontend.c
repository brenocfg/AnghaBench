#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct vp7045_fe_state {int /*<<< orphan*/  d; } ;
struct dtv_frontend_properties {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {struct vp7045_fe_state* demodulator_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TUNER_COMMAND ; 
 int /*<<< orphan*/  vp7045_usb_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vp7045_fe_set_frontend(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *fep = &fe->dtv_property_cache;
	struct vp7045_fe_state *state = fe->demodulator_priv;
	u8 buf[5];
	u32 freq = fep->frequency / 1000;

	buf[0] = (freq >> 16) & 0xff;
	buf[1] = (freq >>  8) & 0xff;
	buf[2] =  freq        & 0xff;
	buf[3] = 0;

	switch (fep->bandwidth_hz) {
	case 8000000:
		buf[4] = 8;
		break;
	case 7000000:
		buf[4] = 7;
		break;
	case 6000000:
		buf[4] = 6;
		break;
	default:
		return -EINVAL;
	}

	vp7045_usb_op(state->d,LOCK_TUNER_COMMAND,buf,5,NULL,0,200);
	return 0;
}