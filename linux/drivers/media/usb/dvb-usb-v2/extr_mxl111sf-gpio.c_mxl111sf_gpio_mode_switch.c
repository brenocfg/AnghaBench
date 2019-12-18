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
struct mxl111sf_state {int dummy; } ;

/* Variables and functions */
#define  MXL111SF_GPIO_MOD_ATSC 129 
#define  MXL111SF_GPIO_MOD_MH 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mxl111sf_init_port_expander (struct mxl111sf_state*) ; 
 int /*<<< orphan*/  mxl111sf_set_gpio (struct mxl111sf_state*,int,int) ; 
 int /*<<< orphan*/  mxl_debug (char*,unsigned int) ; 

int mxl111sf_gpio_mode_switch(struct mxl111sf_state *state, unsigned int mode)
{
/*	GPO:
 *	3 - ATSC/MH#   | 1 = ATSC transport, 0 = MH transport      | default 0
 *	4 - ATSC_RST## | 1 = ATSC enable, 0 = ATSC Reset           | default 0
 *	5 - ATSC_EN    | 1 = ATSC power enable, 0 = ATSC power off | default 0
 *	6 - MH_RESET#  | 1 = MH enable, 0 = MH Reset               | default 0
 *	7 - MH_EN      | 1 = MH power enable, 0 = MH power off     | default 0
 */
	mxl_debug("(%d)", mode);

	switch (mode) {
	case MXL111SF_GPIO_MOD_MH:
		mxl111sf_set_gpio(state, 4, 0);
		mxl111sf_set_gpio(state, 5, 0);
		msleep(50);
		mxl111sf_set_gpio(state, 7, 1);
		msleep(50);
		mxl111sf_set_gpio(state, 6, 1);
		msleep(50);

		mxl111sf_set_gpio(state, 3, 0);
		break;
	case MXL111SF_GPIO_MOD_ATSC:
		mxl111sf_set_gpio(state, 6, 0);
		mxl111sf_set_gpio(state, 7, 0);
		msleep(50);
		mxl111sf_set_gpio(state, 5, 1);
		msleep(50);
		mxl111sf_set_gpio(state, 4, 1);
		msleep(50);
		mxl111sf_set_gpio(state, 3, 1);
		break;
	default: /* DVBT / STANDBY */
		mxl111sf_init_port_expander(state);
		break;
	}
	return 0;
}