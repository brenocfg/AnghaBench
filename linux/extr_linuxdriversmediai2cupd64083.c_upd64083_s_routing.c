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
struct v4l2_subdev {int dummy; } ;
struct upd64083_state {int mode; int ext_y_adc; int* regs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t R00 ; 
 size_t R02 ; 
 int UPD64083_EXT_Y_ADC ; 
 struct upd64083_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  upd64083_write (struct v4l2_subdev*,size_t,int) ; 

__attribute__((used)) static int upd64083_s_routing(struct v4l2_subdev *sd,
			      u32 input, u32 output, u32 config)
{
	struct upd64083_state *state = to_state(sd);
	u8 r00, r02;

	if (input > 7 || (input & 6) == 6)
		return -EINVAL;
	state->mode = (input & 3) << 6;
	state->ext_y_adc = (input & UPD64083_EXT_Y_ADC) << 3;
	r00 = (state->regs[R00] & ~(3 << 6)) | state->mode;
	r02 = (state->regs[R02] & ~(1 << 5)) | state->ext_y_adc;
	upd64083_write(sd, R00, r00);
	upd64083_write(sd, R02, r02);
	return 0;
}