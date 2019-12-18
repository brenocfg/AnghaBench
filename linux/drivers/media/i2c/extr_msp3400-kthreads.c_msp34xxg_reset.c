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
struct msp_state {int route_in; int std; int i2s_mode; scalar_t__ has_nicam; scalar_t__ has_i2s_conf; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int msp34xxg_modus (struct i2c_client*) ; 
 int /*<<< orphan*/  msp34xxg_set_sources (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_reset (struct i2c_client*) ; 
 int msp_stereo_thresh ; 
 int /*<<< orphan*/  msp_write_dem (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  msp_write_dsp (struct i2c_client*,int,int) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msp34xxg_reset(struct i2c_client *client)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	int tuner = (state->route_in >> 3) & 1;
	int modus;

	/* initialize std to 1 (autodetect) to signal that no standard is
	   selected yet. */
	state->std = 1;

	msp_reset(client);

	if (state->has_i2s_conf)
		msp_write_dem(client, 0x40, state->i2s_mode);

	/* step-by-step initialisation, as described in the manual */
	modus = msp34xxg_modus(client);
	modus |= tuner ? 0x100 : 0;
	msp_write_dem(client, 0x30, modus);

	/* write the dsps that may have an influence on
	   standard/audio autodetection right now */
	msp34xxg_set_sources(client);

	msp_write_dsp(client, 0x0d, 0x1900); /* scart */
	msp_write_dsp(client, 0x0e, 0x3000); /* FM */
	if (state->has_nicam)
		msp_write_dsp(client, 0x10, 0x5a00); /* nicam */

	/* set identification threshold. Personally, I
	 * I set it to a higher value than the default
	 * of 0x190 to ignore noisy stereo signals.
	 * this needs tuning. (recommended range 0x00a0-0x03c0)
	 * 0x7f0 = forced mono mode
	 *
	 * a2 threshold for stereo/bilingual.
	 * Note: this register is part of the Manual/Compatibility mode.
	 * It is supported by all 'G'-family chips.
	 */
	msp_write_dem(client, 0x22, msp_stereo_thresh);
}