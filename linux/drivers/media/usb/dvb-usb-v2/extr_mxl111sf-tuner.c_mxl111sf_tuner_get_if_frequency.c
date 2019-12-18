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
typedef  int u32 ;
struct mxl111sf_tuner_state {int if_freq; } ;
struct dvb_frontend {struct mxl111sf_tuner_state* tuner_priv; } ;

/* Variables and functions */
#define  MXL_IF_35_25 139 
#define  MXL_IF_36 138 
#define  MXL_IF_36_15 137 
#define  MXL_IF_44 136 
#define  MXL_IF_4_0 135 
#define  MXL_IF_4_5 134 
#define  MXL_IF_4_57 133 
#define  MXL_IF_5_0 132 
#define  MXL_IF_5_38 131 
#define  MXL_IF_6_0 130 
#define  MXL_IF_6_28 129 
#define  MXL_IF_7_2 128 

__attribute__((used)) static int mxl111sf_tuner_get_if_frequency(struct dvb_frontend *fe,
					   u32 *frequency)
{
	struct mxl111sf_tuner_state *state = fe->tuner_priv;

	*frequency = 0;

	switch (state->if_freq) {
	case MXL_IF_4_0:   /* 4.0   MHz */
		*frequency = 4000000;
		break;
	case MXL_IF_4_5:   /* 4.5   MHz */
		*frequency = 4500000;
		break;
	case MXL_IF_4_57:  /* 4.57  MHz */
		*frequency = 4570000;
		break;
	case MXL_IF_5_0:   /* 5.0   MHz */
		*frequency = 5000000;
		break;
	case MXL_IF_5_38:  /* 5.38  MHz */
		*frequency = 5380000;
		break;
	case MXL_IF_6_0:   /* 6.0   MHz */
		*frequency = 6000000;
		break;
	case MXL_IF_6_28:  /* 6.28  MHz */
		*frequency = 6280000;
		break;
	case MXL_IF_7_2:   /* 7.2   MHz */
		*frequency = 7200000;
		break;
	case MXL_IF_35_25: /* 35.25 MHz */
		*frequency = 35250000;
		break;
	case MXL_IF_36:    /* 36    MHz */
		*frequency = 36000000;
		break;
	case MXL_IF_36_15: /* 36.15 MHz */
		*frequency = 36150000;
		break;
	case MXL_IF_44:    /* 44    MHz */
		*frequency = 44000000;
		break;
	}
	return 0;
}