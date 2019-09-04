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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct mxl5005s_state {size_t Init_Ctrl_Num; size_t CH_Ctrl_Num; TYPE_2__* CH_Ctrl; TYPE_1__* Init_Ctrl; } ;
struct dvb_frontend {struct mxl5005s_state* tuner_priv; } ;
struct TYPE_4__ {size_t Ctrl_Num; size_t size; int* val; } ;
struct TYPE_3__ {size_t Ctrl_Num; size_t size; int* val; } ;

/* Variables and functions */

__attribute__((used)) static u16 MXL_ControlRead(struct dvb_frontend *fe, u16 controlNum, u32 *value)
{
	struct mxl5005s_state *state = fe->tuner_priv;
	u32 ctrlVal ;
	u16 i, k ;

	for (i = 0; i < state->Init_Ctrl_Num ; i++) {

		if (controlNum == state->Init_Ctrl[i].Ctrl_Num) {

			ctrlVal = 0;
			for (k = 0; k < state->Init_Ctrl[i].size; k++)
				ctrlVal += state->Init_Ctrl[i].val[k] * (1<<k);
			*value = ctrlVal;
			return 0;
		}
	}

	for (i = 0; i < state->CH_Ctrl_Num ; i++) {

		if (controlNum == state->CH_Ctrl[i].Ctrl_Num) {

			ctrlVal = 0;
			for (k = 0; k < state->CH_Ctrl[i].size; k++)
				ctrlVal += state->CH_Ctrl[i].val[k] * (1 << k);
			*value = ctrlVal;
			return 0;

		}
	}

#ifdef _MXL_INTERNAL
	for (i = 0; i < state->MXL_Ctrl_Num ; i++) {

		if (controlNum == state->MXL_Ctrl[i].Ctrl_Num) {

			ctrlVal = 0;
			for (k = 0; k < state->MXL_Ctrl[i].size; k++)
				ctrlVal += state->MXL_Ctrl[i].val[k] * (1<<k);
			*value = ctrlVal;
			return 0;

		}
	}
#endif
	return 1;
}