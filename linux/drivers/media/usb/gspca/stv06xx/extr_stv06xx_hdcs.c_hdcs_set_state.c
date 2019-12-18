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
struct sd {struct hdcs* sensor_priv; } ;
struct hdcs {int state; } ;
typedef  enum hdcs_power_state { ____Placeholder_hdcs_power_state } hdcs_power_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDCS_REG_CONTROL (struct sd*) ; 
 int /*<<< orphan*/  HDCS_RUN_ENABLE ; 
 int /*<<< orphan*/  HDCS_SLEEP_MODE ; 
 int HDCS_STATE_IDLE ; 
#define  HDCS_STATE_RUN 129 
#define  HDCS_STATE_SLEEP 128 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdcs_set_state(struct sd *sd, enum hdcs_power_state state)
{
	struct hdcs *hdcs = sd->sensor_priv;
	u8 val;
	int ret;

	if (hdcs->state == state)
		return 0;

	/* we need to go idle before running or sleeping */
	if (hdcs->state != HDCS_STATE_IDLE) {
		ret = stv06xx_write_sensor(sd, HDCS_REG_CONTROL(sd), 0);
		if (ret)
			return ret;
	}

	hdcs->state = HDCS_STATE_IDLE;

	if (state == HDCS_STATE_IDLE)
		return 0;

	switch (state) {
	case HDCS_STATE_SLEEP:
		val = HDCS_SLEEP_MODE;
		break;

	case HDCS_STATE_RUN:
		val = HDCS_RUN_ENABLE;
		break;

	default:
		return -EINVAL;
	}

	ret = stv06xx_write_sensor(sd, HDCS_REG_CONTROL(sd), val);

	/* Update the state if the write succeeded */
	if (!ret)
		hdcs->state = state;

	return ret;
}