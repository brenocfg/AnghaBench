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
typedef  int u16 ;
struct dtv_frontend_properties {int modulation; int hierarchy; int code_rate_HP; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FEC_1_2 142 
#define  FEC_2_3 141 
#define  FEC_3_4 140 
#define  FEC_5_6 139 
#define  FEC_7_8 138 
#define  FEC_AUTO 137 
#define  HIERARCHY_1 136 
#define  HIERARCHY_2 135 
#define  HIERARCHY_4 134 
#define  HIERARCHY_AUTO 133 
#define  HIERARCHY_NONE 132 
#define  QAM_16 131 
#define  QAM_64 130 
#define  QAM_AUTO 129 
#define  QPSK 128 

__attribute__((used)) static int configure_reg0xc05(struct dtv_frontend_properties *p, u16 *reg0xc05)
{
	int known_parameters = 1;

	*reg0xc05 = 0x000;

	switch (p->modulation) {
	case QPSK:
		break;
	case QAM_16:
		*reg0xc05 |= (1 << 10);
		break;
	case QAM_64:
		*reg0xc05 |= (2 << 10);
		break;
	case QAM_AUTO:
		known_parameters = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (p->hierarchy) {
	case HIERARCHY_NONE:
		break;
	case HIERARCHY_1:
		*reg0xc05 |= (1 << 7);
		break;
	case HIERARCHY_2:
		*reg0xc05 |= (2 << 7);
		break;
	case HIERARCHY_4:
		*reg0xc05 |= (3 << 7);
		break;
	case HIERARCHY_AUTO:
		known_parameters = 0;
		break;
	default:
		return -EINVAL;
	}

	switch (p->code_rate_HP) {
	case FEC_1_2:
		break;
	case FEC_2_3:
		*reg0xc05 |= (1 << 3);
		break;
	case FEC_3_4:
		*reg0xc05 |= (2 << 3);
		break;
	case FEC_5_6:
		*reg0xc05 |= (3 << 3);
		break;
	case FEC_7_8:
		*reg0xc05 |= (4 << 3);
		break;
	case FEC_AUTO:
		known_parameters = 0;
		break;
	default:
		return -EINVAL;
	}

	if (known_parameters)
		*reg0xc05 |= (2 << 1);	/* use specified parameters */
	else
		*reg0xc05 |= (1 << 1);	/* enable autoprobing */

	return 0;
}