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
struct v4l2_subdev {int dummy; } ;
struct s5k4ecgx {int set_params; } ;

/* Variables and functions */
 int __s5k4ecgx_power_off (struct s5k4ecgx*) ; 
 int __s5k4ecgx_power_on (struct s5k4ecgx*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  msleep (int) ; 
 int s5k4ecgx_init_sensor (struct v4l2_subdev*) ; 
 struct s5k4ecgx* to_s5k4ecgx (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int s5k4ecgx_s_power(struct v4l2_subdev *sd, int on)
{
	struct s5k4ecgx *priv = to_s5k4ecgx(sd);
	int ret;

	v4l2_dbg(1, debug, sd, "Switching %s\n", on ? "on" : "off");

	if (on) {
		ret = __s5k4ecgx_power_on(priv);
		if (ret < 0)
			return ret;
		/* Time to stabilize sensor */
		msleep(100);
		ret = s5k4ecgx_init_sensor(sd);
		if (ret < 0)
			__s5k4ecgx_power_off(priv);
		else
			priv->set_params = 1;
	} else {
		ret = __s5k4ecgx_power_off(priv);
	}

	return ret;
}