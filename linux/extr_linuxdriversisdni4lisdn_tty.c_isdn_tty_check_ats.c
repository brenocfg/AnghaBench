#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int xmit_size; } ;
typedef  TYPE_1__ modem_info ;
struct TYPE_6__ {int /*<<< orphan*/ * mdmreg; } ;
typedef  TYPE_2__ atemu ;

/* Variables and functions */
 int ISDN_PROTO_L2_MAX ; 
#define  ISDN_PROTO_L2_V11019 135 
#define  ISDN_PROTO_L2_V11038 134 
#define  ISDN_PROTO_L2_V11096 133 
 int ISDN_SERIAL_XMIT_MAX ; 
#define  REG_L2PROT 132 
#define  REG_PLAN 131 
#define  REG_PSIZE 130 
#define  REG_SCREEN 129 
#define  REG_SI1I 128 

__attribute__((used)) static int
isdn_tty_check_ats(int mreg, int mval, modem_info *info, atemu *m)
{
	/* Some plausibility checks */
	switch (mreg) {
	case REG_L2PROT:
		if (mval > ISDN_PROTO_L2_MAX)
			return 1;
		break;
	case REG_PSIZE:
		if ((mval * 16) > ISDN_SERIAL_XMIT_MAX)
			return 1;
#ifdef CONFIG_ISDN_AUDIO
		if ((m->mdmreg[REG_SI1] & 1) && (mval > VBUFX))
			return 1;
#endif
		info->xmit_size = mval * 16;
		switch (m->mdmreg[REG_L2PROT]) {
		case ISDN_PROTO_L2_V11096:
		case ISDN_PROTO_L2_V11019:
		case ISDN_PROTO_L2_V11038:
			info->xmit_size /= 10;
		}
		break;
	case REG_SI1I:
	case REG_PLAN:
	case REG_SCREEN:
		/* readonly registers */
		return 1;
	}
	return 0;
}