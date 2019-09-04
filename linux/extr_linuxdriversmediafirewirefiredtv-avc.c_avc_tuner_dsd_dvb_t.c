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
struct firedtv {scalar_t__ avc_data; } ;
struct dtv_frontend_properties {int bandwidth_hz; int modulation; int hierarchy; int code_rate_HP; int code_rate_LP; int guard_interval; int transmission_mode; int frequency; } ;
struct avc_command_frame {int* operand; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_OPCODE_DSD ; 
#define  FEC_1_2 148 
#define  FEC_2_3 147 
#define  FEC_3_4 146 
#define  FEC_5_6 145 
#define  FEC_7_8 144 
 int FEC_AUTO ; 
#define  GUARD_INTERVAL_1_16 143 
#define  GUARD_INTERVAL_1_32 142 
#define  GUARD_INTERVAL_1_4 141 
#define  GUARD_INTERVAL_1_8 140 
#define  GUARD_INTERVAL_AUTO 139 
#define  HIERARCHY_1 138 
#define  HIERARCHY_2 137 
#define  HIERARCHY_4 136 
#define  HIERARCHY_AUTO 135 
#define  HIERARCHY_NONE 134 
#define  QAM_16 133 
#define  QAM_64 132 
 int QAM_AUTO ; 
#define  QPSK 131 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_8K 129 
#define  TRANSMISSION_MODE_AUTO 128 
 int add_pid_filter (struct firedtv*,int*) ; 

__attribute__((used)) static int avc_tuner_dsd_dvb_t(struct firedtv *fdtv,
			       struct dtv_frontend_properties *p)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_DSD;

	c->operand[0] = 0;    /* source plug */
	c->operand[1] = 0xd2; /* subfunction replace */
	c->operand[2] = 0x20; /* system id = DVB */
	c->operand[3] = 0x00; /* antenna number */
	c->operand[4] = 0x0c; /* system_specific_multiplex selection_length */

	/* multiplex_valid_flags, high byte */
	c->operand[5] =
	      0 << 7 /* reserved */
	    | 1 << 6 /* CenterFrequency */
	    | (p->bandwidth_hz != 0        ? 1 << 5 : 0)
	    | (p->modulation  != QAM_AUTO              ? 1 << 4 : 0)
	    | (p->hierarchy != HIERARCHY_AUTO ? 1 << 3 : 0)
	    | (p->code_rate_HP   != FEC_AUTO              ? 1 << 2 : 0)
	    | (p->code_rate_LP   != FEC_AUTO              ? 1 << 1 : 0)
	    | (p->guard_interval != GUARD_INTERVAL_AUTO   ? 1 << 0 : 0);

	/* multiplex_valid_flags, low byte */
	c->operand[6] =
	      0 << 7 /* NetworkID */
	    | (p->transmission_mode != TRANSMISSION_MODE_AUTO ? 1 << 6 : 0)
	    | 0 << 5 /* OtherFrequencyFlag */
	    | 0 << 0 /* reserved */ ;

	c->operand[7]  = 0x0;
	c->operand[8]  = (p->frequency / 10) >> 24;
	c->operand[9]  = ((p->frequency / 10) >> 16) & 0xff;
	c->operand[10] = ((p->frequency / 10) >>  8) & 0xff;
	c->operand[11] = (p->frequency / 10) & 0xff;

	switch (p->bandwidth_hz) {
	case 7000000:	c->operand[12] = 0x20; break;
	case 8000000:
	case 6000000:	/* not defined by AVC spec */
	case 0:
	default:		c->operand[12] = 0x00;
	}

	switch (p->modulation) {
	case QAM_16:	c->operand[13] = 1 << 6; break;
	case QAM_64:	c->operand[13] = 2 << 6; break;
	case QPSK:
	default:	c->operand[13] = 0x00;
	}

	switch (p->hierarchy) {
	case HIERARCHY_1:	c->operand[13] |= 1 << 3; break;
	case HIERARCHY_2:	c->operand[13] |= 2 << 3; break;
	case HIERARCHY_4:	c->operand[13] |= 3 << 3; break;
	case HIERARCHY_AUTO:
	case HIERARCHY_NONE:
	default:		break;
	}

	switch (p->code_rate_HP) {
	case FEC_2_3:	c->operand[13] |= 1; break;
	case FEC_3_4:	c->operand[13] |= 2; break;
	case FEC_5_6:	c->operand[13] |= 3; break;
	case FEC_7_8:	c->operand[13] |= 4; break;
	case FEC_1_2:
	default:	break;
	}

	switch (p->code_rate_LP) {
	case FEC_2_3:	c->operand[14] = 1 << 5; break;
	case FEC_3_4:	c->operand[14] = 2 << 5; break;
	case FEC_5_6:	c->operand[14] = 3 << 5; break;
	case FEC_7_8:	c->operand[14] = 4 << 5; break;
	case FEC_1_2:
	default:	c->operand[14] = 0x00; break;
	}

	switch (p->guard_interval) {
	case GUARD_INTERVAL_1_16:	c->operand[14] |= 1 << 3; break;
	case GUARD_INTERVAL_1_8:	c->operand[14] |= 2 << 3; break;
	case GUARD_INTERVAL_1_4:	c->operand[14] |= 3 << 3; break;
	case GUARD_INTERVAL_1_32:
	case GUARD_INTERVAL_AUTO:
	default:			break;
	}

	switch (p->transmission_mode) {
	case TRANSMISSION_MODE_8K:	c->operand[14] |= 1 << 1; break;
	case TRANSMISSION_MODE_2K:
	case TRANSMISSION_MODE_AUTO:
	default:			break;
	}

	c->operand[15] = 0x00; /* network_ID[0] */
	c->operand[16] = 0x00; /* network_ID[1] */

	return 17 + add_pid_filter(fdtv, &c->operand[17]);
}