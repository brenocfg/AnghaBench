#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smiapp_sensor {int /*<<< orphan*/  mutex; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMIAPP_MODE_SELECT_SOFTWARE_STANDBY ; 
 int /*<<< orphan*/  SMIAPP_REG_U8_MODE_SELECT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_streamoff ; 
 int smiapp_call_quirk (struct smiapp_sensor*,int /*<<< orphan*/ ) ; 
 int smiapp_write (struct smiapp_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_stop_streaming(struct smiapp_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	int rval;

	mutex_lock(&sensor->mutex);
	rval = smiapp_write(sensor, SMIAPP_REG_U8_MODE_SELECT,
			    SMIAPP_MODE_SELECT_SOFTWARE_STANDBY);
	if (rval)
		goto out;

	rval = smiapp_call_quirk(sensor, post_streamoff);
	if (rval)
		dev_err(&client->dev, "post_streamoff quirks failed\n");

out:
	mutex_unlock(&sensor->mutex);
	return rval;
}