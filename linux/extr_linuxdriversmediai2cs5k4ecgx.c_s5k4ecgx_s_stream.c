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
struct s5k4ecgx {int streaming; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __s5k4ecgx_s_stream (struct s5k4ecgx*,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5k4ecgx* to_s5k4ecgx (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int s5k4ecgx_s_stream(struct v4l2_subdev *sd, int on)
{
	struct s5k4ecgx *priv = to_s5k4ecgx(sd);
	int ret = 0;

	v4l2_dbg(1, debug, sd, "Turn streaming %s\n", on ? "on" : "off");

	mutex_lock(&priv->lock);

	if (priv->streaming == !on) {
		ret = __s5k4ecgx_s_stream(priv, on);
		if (!ret)
			priv->streaming = on & 1;
	}

	mutex_unlock(&priv->lock);
	return ret;
}