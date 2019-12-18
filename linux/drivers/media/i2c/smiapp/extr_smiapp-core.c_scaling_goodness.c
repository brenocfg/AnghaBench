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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct smiapp_sensor {int* limits; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SCALING_GOODNESS ; 
 scalar_t__ SCALING_GOODNESS_EXTREME ; 
 size_t SMIAPP_LIMIT_MIN_X_OUTPUT_SIZE ; 
 int V4L2_SEL_FLAG_GE ; 
 int V4L2_SEL_FLAG_LE ; 
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int,int,int) ; 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int scaling_goodness(struct v4l2_subdev *subdev, int w, int ask_w,
			    int h, int ask_h, u32 flags)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	int val = 0;

	w &= ~1;
	ask_w &= ~1;
	h &= ~1;
	ask_h &= ~1;

	if (flags & V4L2_SEL_FLAG_GE) {
		if (w < ask_w)
			val -= SCALING_GOODNESS;
		if (h < ask_h)
			val -= SCALING_GOODNESS;
	}

	if (flags & V4L2_SEL_FLAG_LE) {
		if (w > ask_w)
			val -= SCALING_GOODNESS;
		if (h > ask_h)
			val -= SCALING_GOODNESS;
	}

	val -= abs(w - ask_w);
	val -= abs(h - ask_h);

	if (w < sensor->limits[SMIAPP_LIMIT_MIN_X_OUTPUT_SIZE])
		val -= SCALING_GOODNESS_EXTREME;

	dev_dbg(&client->dev, "w %d ask_w %d h %d ask_h %d goodness %d\n",
		w, ask_w, h, ask_h, val);

	return val;
}