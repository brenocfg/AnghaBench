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
struct upd64031a_state {int gr_mode; int direct_3dycs_connect; int ext_comp_sync; int ext_vert_sync; int* regs; } ;

/* Variables and functions */
 int DIRECT_3DYCS_CONNECT_MASK ; 
 int GR_MODE_MASK ; 
 size_t R00 ; 
 size_t R05 ; 
 size_t R08 ; 
 int SYNC_CIRCUIT_MASK ; 
 int UPD64031A_COMPOSITE_EXTERNAL ; 
 int UPD64031A_VERTICAL_EXTERNAL ; 
 struct upd64031a_state* to_state (struct v4l2_subdev*) ; 
 int upd64031a_s_frequency (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upd64031a_write (struct v4l2_subdev*,size_t,int) ; 

__attribute__((used)) static int upd64031a_s_routing(struct v4l2_subdev *sd,
			       u32 input, u32 output, u32 config)
{
	struct upd64031a_state *state = to_state(sd);
	u8 r00, r05, r08;

	state->gr_mode = (input & 3) << 6;
	state->direct_3dycs_connect = (input & 0xc) << 4;
	state->ext_comp_sync =
		(input & UPD64031A_COMPOSITE_EXTERNAL) << 1;
	state->ext_vert_sync =
		(input & UPD64031A_VERTICAL_EXTERNAL) << 2;
	r00 = (state->regs[R00] & ~GR_MODE_MASK) | state->gr_mode;
	r05 = (state->regs[R00] & ~SYNC_CIRCUIT_MASK) |
		state->ext_comp_sync | state->ext_vert_sync;
	r08 = (state->regs[R08] & ~DIRECT_3DYCS_CONNECT_MASK) |
		state->direct_3dycs_connect;
	upd64031a_write(sd, R00, r00);
	upd64031a_write(sd, R05, r05);
	upd64031a_write(sd, R08, r08);
	return upd64031a_s_frequency(sd, NULL);
}