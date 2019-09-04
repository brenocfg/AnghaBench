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
typedef  int /*<<< orphan*/  u8 ;
struct au8522_state {int vid_input; } ;

/* Variables and functions */
#define  AU8522_COMPOSITE_CH1 134 
#define  AU8522_COMPOSITE_CH2 133 
#define  AU8522_COMPOSITE_CH3 132 
#define  AU8522_COMPOSITE_CH4 131 
#define  AU8522_COMPOSITE_CH4_SIF 130 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_CVBS_CH1 ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_CVBS_CH2 ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_CVBS_CH3 ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_CVBS_CH4 ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_CVBS_CH4_SIF ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13 ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24 ; 
#define  AU8522_SVIDEO_CH13 129 
#define  AU8522_SVIDEO_CH24 128 
 int /*<<< orphan*/  au8522_setup_cvbs_mode (struct au8522_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au8522_setup_cvbs_tuner_mode (struct au8522_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au8522_setup_svideo_mode (struct au8522_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int,int) ; 

__attribute__((used)) static void au8522_video_set(struct au8522_state *state)
{
	u8 input_mode;

	au8522_writereg(state, 0xa4, 1 << 5);

	switch (state->vid_input) {
	case AU8522_COMPOSITE_CH1:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH1;
		au8522_setup_cvbs_mode(state, input_mode);
		break;
	case AU8522_COMPOSITE_CH2:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH2;
		au8522_setup_cvbs_mode(state, input_mode);
		break;
	case AU8522_COMPOSITE_CH3:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH3;
		au8522_setup_cvbs_mode(state, input_mode);
		break;
	case AU8522_COMPOSITE_CH4:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH4;
		au8522_setup_cvbs_mode(state, input_mode);
		break;
	case AU8522_SVIDEO_CH13:
		input_mode = AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH13;
		au8522_setup_svideo_mode(state, input_mode);
		break;
	case AU8522_SVIDEO_CH24:
		input_mode = AU8522_INPUT_CONTROL_REG081H_SVIDEO_CH24;
		au8522_setup_svideo_mode(state, input_mode);
		break;
	default:
	case AU8522_COMPOSITE_CH4_SIF:
		input_mode = AU8522_INPUT_CONTROL_REG081H_CVBS_CH4_SIF;
		au8522_setup_cvbs_tuner_mode(state, input_mode);
		break;
	}
}