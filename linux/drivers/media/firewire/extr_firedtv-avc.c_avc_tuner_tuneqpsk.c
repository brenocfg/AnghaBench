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
struct TYPE_3__ {scalar_t__ delivery_system; int modulation; int rolloff; int pilot; } ;
struct TYPE_4__ {TYPE_1__ dtv_property_cache; } ;
struct firedtv {scalar_t__ type; int voltage; int tone; TYPE_2__ fe; scalar_t__ avc_data; } ;
struct dtv_frontend_properties {int frequency; int symbol_rate; int fec_inner; } ;
struct avc_command_frame {int* operand; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_OPCODE_VENDOR ; 
#define  FEC_1_2 145 
#define  FEC_2_3 144 
#define  FEC_3_4 143 
#define  FEC_4_5 142 
#define  FEC_5_6 141 
#define  FEC_7_8 140 
#define  FEC_8_9 139 
#define  FEC_AUTO 138 
 scalar_t__ FIREDTV_DVB_S2 ; 
#define  PILOT_AUTO 137 
#define  PILOT_OFF 136 
#define  PILOT_ON 135 
#define  PSK_8 134 
#define  QAM_16 133 
#define  QPSK 132 
#define  ROLLOFF_20 131 
#define  ROLLOFF_25 130 
#define  ROLLOFF_35 129 
#define  ROLLOFF_AUTO 128 
 int SEC_TONE_ON ; 
 int SEC_VOLTAGE_18 ; 
 int SFE_VENDOR_DE_COMPANYID_0 ; 
 int SFE_VENDOR_DE_COMPANYID_1 ; 
 int SFE_VENDOR_DE_COMPANYID_2 ; 
 int SFE_VENDOR_OPCODE_TUNE_QPSK ; 
 int SFE_VENDOR_OPCODE_TUNE_QPSK2 ; 
 scalar_t__ SYS_DVBS2 ; 

__attribute__((used)) static int avc_tuner_tuneqpsk(struct firedtv *fdtv,
			      struct dtv_frontend_properties *p)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_VENDOR;

	c->operand[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->operand[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->operand[2] = SFE_VENDOR_DE_COMPANYID_2;
	if (fdtv->type == FIREDTV_DVB_S2)
		c->operand[3] = SFE_VENDOR_OPCODE_TUNE_QPSK2;
	else
		c->operand[3] = SFE_VENDOR_OPCODE_TUNE_QPSK;

	c->operand[4] = (p->frequency >> 24) & 0xff;
	c->operand[5] = (p->frequency >> 16) & 0xff;
	c->operand[6] = (p->frequency >> 8) & 0xff;
	c->operand[7] = p->frequency & 0xff;

	c->operand[8] = ((p->symbol_rate / 1000) >> 8) & 0xff;
	c->operand[9] = (p->symbol_rate / 1000) & 0xff;

	switch (p->fec_inner) {
	case FEC_1_2:	c->operand[10] = 0x1; break;
	case FEC_2_3:	c->operand[10] = 0x2; break;
	case FEC_3_4:	c->operand[10] = 0x3; break;
	case FEC_5_6:	c->operand[10] = 0x4; break;
	case FEC_7_8:	c->operand[10] = 0x5; break;
	case FEC_4_5:
	case FEC_8_9:
	case FEC_AUTO:
	default:	c->operand[10] = 0x0;
	}

	if (fdtv->voltage == 0xff)
		c->operand[11] = 0xff;
	else if (fdtv->voltage == SEC_VOLTAGE_18) /* polarisation */
		c->operand[11] = 0;
	else
		c->operand[11] = 1;

	if (fdtv->tone == 0xff)
		c->operand[12] = 0xff;
	else if (fdtv->tone == SEC_TONE_ON) /* band */
		c->operand[12] = 1;
	else
		c->operand[12] = 0;

	if (fdtv->type == FIREDTV_DVB_S2) {
		if (fdtv->fe.dtv_property_cache.delivery_system == SYS_DVBS2) {
			switch (fdtv->fe.dtv_property_cache.modulation) {
			case QAM_16:		c->operand[13] = 0x1; break;
			case QPSK:		c->operand[13] = 0x2; break;
			case PSK_8:		c->operand[13] = 0x3; break;
			default:		c->operand[13] = 0x2; break;
			}
			switch (fdtv->fe.dtv_property_cache.rolloff) {
			case ROLLOFF_35:	c->operand[14] = 0x2; break;
			case ROLLOFF_20:	c->operand[14] = 0x0; break;
			case ROLLOFF_25:	c->operand[14] = 0x1; break;
			case ROLLOFF_AUTO:
			default:		c->operand[14] = 0x2; break;
			/* case ROLLOFF_NONE:	c->operand[14] = 0xff; break; */
			}
			switch (fdtv->fe.dtv_property_cache.pilot) {
			case PILOT_AUTO:	c->operand[15] = 0x0; break;
			case PILOT_OFF:		c->operand[15] = 0x0; break;
			case PILOT_ON:		c->operand[15] = 0x1; break;
			}
		} else {
			c->operand[13] = 0x1;  /* auto modulation */
			c->operand[14] = 0xff; /* disable rolloff */
			c->operand[15] = 0xff; /* disable pilot */
		}
		return 16;
	} else {
		return 13;
	}
}