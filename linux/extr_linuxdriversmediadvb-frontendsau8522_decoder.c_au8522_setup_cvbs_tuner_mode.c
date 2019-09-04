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
struct au8522_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_CLAMPING_CONTROL_REG083H ; 
 int /*<<< orphan*/  AU8522_INPUT_CONTROL_REG081H ; 
 int /*<<< orphan*/  AU8522_MODULE_CLOCK_CONTROL_REG0A3H ; 
 int AU8522_MODULE_CLOCK_CONTROL_REG0A3H_CVBS ; 
 int /*<<< orphan*/  AU8522_PGA_CONTROL_REG082H ; 
 int /*<<< orphan*/  AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H ; 
 int AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setup_decoder_defaults (struct au8522_state*,int) ; 

__attribute__((used)) static void au8522_setup_cvbs_tuner_mode(struct au8522_state *state,
					 u8 input_mode)
{
	/* here we're going to try the pre-programmed route */
	au8522_writereg(state, AU8522_MODULE_CLOCK_CONTROL_REG0A3H,
			AU8522_MODULE_CLOCK_CONTROL_REG0A3H_CVBS);

	/* It's not clear why we have to have the PGA in automatic mode while
	   enabling clamp control, but it's what Windows does */
	au8522_writereg(state, AU8522_PGA_CONTROL_REG082H, 0x00);

	/* Enable clamping control */
	au8522_writereg(state, AU8522_CLAMPING_CONTROL_REG083H, 0x0e);

	/* Disable automatic PGA (since the CVBS is coming from the tuner) */
	au8522_writereg(state, AU8522_PGA_CONTROL_REG082H, 0x10);

	/* Set input mode to CVBS on channel 4 with SIF audio input enabled */
	au8522_writereg(state, AU8522_INPUT_CONTROL_REG081H, input_mode);

	setup_decoder_defaults(state, false);

	au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_CVBS);
}