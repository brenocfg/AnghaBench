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
struct tuner_simple_priv {int type; size_t nr; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
#define  SYS_ATSC 134 
#define  SYS_DVBC_ANNEX_B 133 
#define  TUNER_PHILIPS_FCV1236D 132 
#define  TUNER_PHILIPS_FMD1216MEX_MK3 131 
#define  TUNER_PHILIPS_FMD1216ME_MK3 130 
#define  TUNER_PHILIPS_TD1316 129 
#define  TUNER_PHILIPS_TUV1236D 128 
 unsigned int* dtv_input ; 
 int /*<<< orphan*/  simple_set_rf_input (struct dvb_frontend*,int*,int*,unsigned int) ; 

__attribute__((used)) static void simple_set_dvb(struct dvb_frontend *fe, u8 *buf,
			   const u32 delsys,
			   const u32 frequency,
			   const u32 bandwidth)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;

	switch (priv->type) {
	case TUNER_PHILIPS_FMD1216ME_MK3:
	case TUNER_PHILIPS_FMD1216MEX_MK3:
		if (bandwidth == 8000000 &&
		    frequency >= 158870000)
			buf[3] |= 0x08;
		break;
	case TUNER_PHILIPS_TD1316:
		/* determine band */
		buf[3] |= (frequency < 161000000) ? 1 :
			  (frequency < 444000000) ? 2 : 4;

		/* setup PLL filter */
		if (bandwidth == 8000000)
			buf[3] |= 1 << 3;
		break;
	case TUNER_PHILIPS_TUV1236D:
	case TUNER_PHILIPS_FCV1236D:
	{
		unsigned int new_rf;

		if (dtv_input[priv->nr])
			new_rf = dtv_input[priv->nr];
		else
			switch (delsys) {
			case SYS_DVBC_ANNEX_B:
				new_rf = 1;
				break;
			case SYS_ATSC:
			default:
				new_rf = 0;
				break;
			}
		simple_set_rf_input(fe, &buf[2], &buf[3], new_rf);
		break;
	}
	default:
		break;
	}
}