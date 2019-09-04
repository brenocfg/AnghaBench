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
struct i2c_client {int dummy; } ;
struct ch7006_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH7006_BCLKOUT ; 
 int /*<<< orphan*/  CH7006_BLACK_LEVEL ; 
 int /*<<< orphan*/  CH7006_BWIDTH ; 
 int /*<<< orphan*/  CH7006_CALC_SUBC_INC0 ; 
 int /*<<< orphan*/  CH7006_CLKMODE ; 
 int /*<<< orphan*/  CH7006_CONTRAST ; 
 int /*<<< orphan*/  CH7006_DETECT ; 
 int /*<<< orphan*/  CH7006_DISPMODE ; 
 int /*<<< orphan*/  CH7006_FFILTER ; 
 int /*<<< orphan*/  CH7006_HPOS ; 
 int /*<<< orphan*/  CH7006_INPUT_FORMAT ; 
 int /*<<< orphan*/  CH7006_INPUT_SYNC ; 
 int /*<<< orphan*/  CH7006_PLLM ; 
 int /*<<< orphan*/  CH7006_PLLN ; 
 int /*<<< orphan*/  CH7006_PLLOV ; 
 int /*<<< orphan*/  CH7006_PLL_CONTROL ; 
 int /*<<< orphan*/  CH7006_POV ; 
 int /*<<< orphan*/  CH7006_POWER ; 
 int /*<<< orphan*/  CH7006_START_ACTIVE ; 
 int /*<<< orphan*/  CH7006_SUBC_INC0 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC1 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC2 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC3 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC4 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC5 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC6 ; 
 int /*<<< orphan*/  CH7006_SUBC_INC7 ; 
 int /*<<< orphan*/  CH7006_VPOS ; 
 int /*<<< orphan*/  ch7006_load_reg (struct i2c_client*,struct ch7006_state*,int /*<<< orphan*/ ) ; 

void ch7006_state_load(struct i2c_client *client,
		       struct ch7006_state *state)
{
	ch7006_load_reg(client, state, CH7006_POWER);

	ch7006_load_reg(client, state, CH7006_DISPMODE);
	ch7006_load_reg(client, state, CH7006_FFILTER);
	ch7006_load_reg(client, state, CH7006_BWIDTH);
	ch7006_load_reg(client, state, CH7006_INPUT_FORMAT);
	ch7006_load_reg(client, state, CH7006_CLKMODE);
	ch7006_load_reg(client, state, CH7006_START_ACTIVE);
	ch7006_load_reg(client, state, CH7006_POV);
	ch7006_load_reg(client, state, CH7006_BLACK_LEVEL);
	ch7006_load_reg(client, state, CH7006_HPOS);
	ch7006_load_reg(client, state, CH7006_VPOS);
	ch7006_load_reg(client, state, CH7006_INPUT_SYNC);
	ch7006_load_reg(client, state, CH7006_DETECT);
	ch7006_load_reg(client, state, CH7006_CONTRAST);
	ch7006_load_reg(client, state, CH7006_PLLOV);
	ch7006_load_reg(client, state, CH7006_PLLM);
	ch7006_load_reg(client, state, CH7006_PLLN);
	ch7006_load_reg(client, state, CH7006_BCLKOUT);
	ch7006_load_reg(client, state, CH7006_SUBC_INC0);
	ch7006_load_reg(client, state, CH7006_SUBC_INC1);
	ch7006_load_reg(client, state, CH7006_SUBC_INC2);
	ch7006_load_reg(client, state, CH7006_SUBC_INC3);
	ch7006_load_reg(client, state, CH7006_SUBC_INC4);
	ch7006_load_reg(client, state, CH7006_SUBC_INC5);
	ch7006_load_reg(client, state, CH7006_SUBC_INC6);
	ch7006_load_reg(client, state, CH7006_SUBC_INC7);
	ch7006_load_reg(client, state, CH7006_PLL_CONTROL);
	ch7006_load_reg(client, state, CH7006_CALC_SUBC_INC0);
}