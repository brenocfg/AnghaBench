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
struct tw9910_priv {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int tw9910_power_off (struct tw9910_priv*) ; 
 int tw9910_power_on (struct tw9910_priv*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tw9910_s_power(struct v4l2_subdev *sd, int on)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tw9910_priv *priv = to_tw9910(client);

	return on ? tw9910_power_on(priv) : tw9910_power_off(priv);
}