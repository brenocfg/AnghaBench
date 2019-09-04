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
struct mxl {TYPE_1__* base; } ;
typedef  enum MXL_BOOL_E { ____Placeholder_MXL_BOOL_E } MXL_BOOL_E ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int MXL_ENABLE ; 
 int MXL_FALSE ; 
#define  MXL_HYDRA_DEVICE_541 137 
#define  MXL_HYDRA_DEVICE_541S 136 
#define  MXL_HYDRA_DEVICE_542 135 
#define  MXL_HYDRA_DEVICE_544 134 
#define  MXL_HYDRA_DEVICE_561 133 
#define  MXL_HYDRA_DEVICE_561S 132 
#define  MXL_HYDRA_DEVICE_568 131 
#define  MXL_HYDRA_DEVICE_581 130 
#define  MXL_HYDRA_DEVICE_581S 129 
#define  MXL_HYDRA_DEVICE_584 128 
 int MXL_TRUE ; 
 int update_by_mnemonic (struct mxl*,int,int,int,int) ; 

__attribute__((used)) static int cfg_ts_pad_mux(struct mxl *state, enum MXL_BOOL_E enable_serial_ts)
{
	int status = 0;
	u32 pad_mux_value = 0;

	if (enable_serial_ts == MXL_TRUE) {
		pad_mux_value = 0;
		if ((state->base->type == MXL_HYDRA_DEVICE_541) ||
		    (state->base->type == MXL_HYDRA_DEVICE_541S))
			pad_mux_value = 2;
	} else {
		if ((state->base->type == MXL_HYDRA_DEVICE_581) ||
		    (state->base->type == MXL_HYDRA_DEVICE_581S))
			pad_mux_value = 2;
		else
			pad_mux_value = 3;
	}

	switch (state->base->type) {
	case MXL_HYDRA_DEVICE_561:
	case MXL_HYDRA_DEVICE_581:
	case MXL_HYDRA_DEVICE_541:
	case MXL_HYDRA_DEVICE_541S:
	case MXL_HYDRA_DEVICE_561S:
	case MXL_HYDRA_DEVICE_581S:
		status |= update_by_mnemonic(state, 0x90000170, 24, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000170, 28, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 0, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 4, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 8, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 12, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 16, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 20, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 24, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000174, 28, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000178, 0, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000178, 4, 3,
					     pad_mux_value);
		status |= update_by_mnemonic(state, 0x90000178, 8, 3,
					     pad_mux_value);
		break;

	case MXL_HYDRA_DEVICE_544:
	case MXL_HYDRA_DEVICE_542:
		status |= update_by_mnemonic(state, 0x9000016C, 4, 3, 1);
		status |= update_by_mnemonic(state, 0x9000016C, 8, 3, 0);
		status |= update_by_mnemonic(state, 0x9000016C, 12, 3, 0);
		status |= update_by_mnemonic(state, 0x9000016C, 16, 3, 0);
		status |= update_by_mnemonic(state, 0x90000170, 0, 3, 0);
		status |= update_by_mnemonic(state, 0x90000178, 12, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 16, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 20, 3, 1);
		status |= update_by_mnemonic(state, 0x90000178, 24, 3, 1);
		status |= update_by_mnemonic(state, 0x9000017C, 0, 3, 1);
		status |= update_by_mnemonic(state, 0x9000017C, 4, 3, 1);
		if (enable_serial_ts == MXL_ENABLE) {
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 0);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, 2);
			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 2);
		} else {
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, 3);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, 1);
			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 1);
		}
		break;

	case MXL_HYDRA_DEVICE_568:
		if (enable_serial_ts == MXL_FALSE) {
			status |= update_by_mnemonic(state,
				0x9000016C, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 20, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 24, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000016C, 28, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 0, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, 5);

			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 16, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 20, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 24, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 28, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000178, 0, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000178, 4, 3, pad_mux_value);

			status |= update_by_mnemonic(state,
				0x90000178, 8, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 12, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 16, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 20, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 24, 3, 5);
			status |= update_by_mnemonic(state,
				0x90000178, 28, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000017C, 0, 3, 5);
			status |= update_by_mnemonic(state,
				0x9000017C, 4, 3, 5);
		} else {
			status |= update_by_mnemonic(state,
				0x90000170, 4, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 8, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 12, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 16, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 20, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 24, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000170, 28, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 0, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 4, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 8, 3, pad_mux_value);
			status |= update_by_mnemonic(state,
				0x90000174, 12, 3, pad_mux_value);
		}
		break;


	case MXL_HYDRA_DEVICE_584:
	default:
		status |= update_by_mnemonic(state,
			0x90000170, 4, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 8, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 12, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 16, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 20, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 24, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000170, 28, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 0, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 4, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 8, 3, pad_mux_value);
		status |= update_by_mnemonic(state,
			0x90000174, 12, 3, pad_mux_value);
		break;
	}
	return status;
}