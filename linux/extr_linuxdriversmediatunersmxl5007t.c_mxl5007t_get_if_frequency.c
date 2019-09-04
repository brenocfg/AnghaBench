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
struct mxl5007t_state {int if_freq; } ;
struct dvb_frontend {struct mxl5007t_state* tuner_priv; } ;

/* Variables and functions */
#define  MxL_IF_35_25_MHZ 138 
#define  MxL_IF_36_15_MHZ 137 
#define  MxL_IF_44_MHZ 136 
#define  MxL_IF_4_57_MHZ 135 
#define  MxL_IF_4_5_MHZ 134 
#define  MxL_IF_4_MHZ 133 
#define  MxL_IF_5_38_MHZ 132 
#define  MxL_IF_5_MHZ 131 
#define  MxL_IF_6_28_MHZ 130 
#define  MxL_IF_6_MHZ 129 
#define  MxL_IF_9_1915_MHZ 128 

__attribute__((used)) static int mxl5007t_get_if_frequency(struct dvb_frontend *fe, u32 *frequency)
{
	struct mxl5007t_state *state = fe->tuner_priv;

	*frequency = 0;

	switch (state->if_freq) {
	case MxL_IF_4_MHZ:
		*frequency = 4000000;
		break;
	case MxL_IF_4_5_MHZ:
		*frequency = 4500000;
		break;
	case MxL_IF_4_57_MHZ:
		*frequency = 4570000;
		break;
	case MxL_IF_5_MHZ:
		*frequency = 5000000;
		break;
	case MxL_IF_5_38_MHZ:
		*frequency = 5380000;
		break;
	case MxL_IF_6_MHZ:
		*frequency = 6000000;
		break;
	case MxL_IF_6_28_MHZ:
		*frequency = 6280000;
		break;
	case MxL_IF_9_1915_MHZ:
		*frequency = 9191500;
		break;
	case MxL_IF_35_25_MHZ:
		*frequency = 35250000;
		break;
	case MxL_IF_36_15_MHZ:
		*frequency = 36150000;
		break;
	case MxL_IF_44_MHZ:
		*frequency = 44000000;
		break;
	}
	return 0;
}