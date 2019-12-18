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
struct au8522_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_AUDIO_VOLUME_L_REG0F2H ; 
 int /*<<< orphan*/  AU8522_AUDIO_VOLUME_REG0F4H ; 
 int /*<<< orphan*/  AU8522_AUDIO_VOLUME_R_REG0F3H ; 
 int /*<<< orphan*/  AU8522_I2S_CTRL_2_REG112H ; 
 int /*<<< orphan*/  AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H ; 
 int AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_SVIDEO ; 
 int /*<<< orphan*/  AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void disable_audio_input(struct au8522_state *state)
{
	au8522_writereg(state, AU8522_AUDIO_VOLUME_L_REG0F2H, 0x00);
	au8522_writereg(state, AU8522_AUDIO_VOLUME_R_REG0F3H, 0x00);
	au8522_writereg(state, AU8522_AUDIO_VOLUME_REG0F4H, 0x00);

	au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_1_REG0A5H, 0x04);
	au8522_writereg(state, AU8522_I2S_CTRL_2_REG112H, 0x02);

	au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
			AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H_SVIDEO);
}