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
struct msp_state {int opmode; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
#define  OPMODE_AUTODETECT 130 
#define  OPMODE_AUTOSELECT 129 
#define  OPMODE_MANUAL 128 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int msp3400c_detect_stereo (struct i2c_client*) ; 
 int msp34xxg_detect_stereo (struct i2c_client*) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 

int msp_detect_stereo(struct i2c_client *client)
{
	struct msp_state *state  = to_state(i2c_get_clientdata(client));

	switch (state->opmode) {
	case OPMODE_MANUAL:
	case OPMODE_AUTODETECT:
		return msp3400c_detect_stereo(client);
	case OPMODE_AUTOSELECT:
		return msp34xxg_detect_stereo(client);
	}
	return 0;
}