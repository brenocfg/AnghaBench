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
struct s5k4ecgx {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __s5k4ecgx_power_off (struct s5k4ecgx*) ; 
 int __s5k4ecgx_power_on (struct s5k4ecgx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int s5k4ecgx_read_fw_ver (struct v4l2_subdev*) ; 
 struct s5k4ecgx* to_s5k4ecgx (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k4ecgx_registered(struct v4l2_subdev *sd)
{
	int ret;
	struct s5k4ecgx *priv = to_s5k4ecgx(sd);

	mutex_lock(&priv->lock);
	ret = __s5k4ecgx_power_on(priv);
	if (!ret) {
		ret = s5k4ecgx_read_fw_ver(sd);
		__s5k4ecgx_power_off(priv);
	}
	mutex_unlock(&priv->lock);

	return ret;
}