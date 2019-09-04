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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  TUNER_SET_CONFIG 128 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int tuner_s_config (struct v4l2_subdev*,void*) ; 

__attribute__((used)) static int tuner_command(struct i2c_client *client, unsigned cmd, void *arg)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);

	/* TUNER_SET_CONFIG is still called by tuner-simple.c, so we have
	   to handle it here.
	   There must be a better way of doing this... */
	switch (cmd) {
	case TUNER_SET_CONFIG:
		return tuner_s_config(sd, arg);
	}
	return -ENOIOCTLCMD;
}