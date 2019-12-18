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
struct msp_state {int in_scart; int acb; int /*<<< orphan*/  i2s_mode; scalar_t__ has_i2s_conf; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg_lvl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_write_dem (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp_write_dsp (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/ * scart_names ; 
 int** scarts ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 

void msp_set_scart(struct i2c_client *client, int in, int out)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));

	state->in_scart = in;

	if (in >= 0 && in <= 7 && out >= 0 && out <= 2) {
		if (-1 == scarts[out][in + 1])
			return;

		state->acb &= ~scarts[out][0];
		state->acb |=  scarts[out][in + 1];
	} else
		state->acb = 0xf60; /* Mute Input and SCART 1 Output */

	dev_dbg_lvl(&client->dev, 1, msp_debug, "scart switch: %s => %d (ACB=0x%04x)\n",
					scart_names[in], out, state->acb);
	msp_write_dsp(client, 0x13, state->acb);

	/* Sets I2S speed 0 = 1.024 Mbps, 1 = 2.048 Mbps */
	if (state->has_i2s_conf)
		msp_write_dem(client, 0x40, state->i2s_mode);
}