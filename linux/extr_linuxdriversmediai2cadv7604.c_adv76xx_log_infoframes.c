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
typedef  union hdmi_infoframe {int dummy; } hdmi_infoframe ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  adv76xx_cri ; 
 scalar_t__ adv76xx_read_infoframe (struct v4l2_subdev*,int,union hdmi_infoframe*) ; 
 int /*<<< orphan*/  hdmi_infoframe_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,union hdmi_infoframe*) ; 
 int /*<<< orphan*/  is_hdmi (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static void adv76xx_log_infoframes(struct v4l2_subdev *sd)
{
	int i;

	if (!is_hdmi(sd)) {
		v4l2_info(sd, "receive DVI-D signal, no infoframes\n");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(adv76xx_cri); i++) {
		union hdmi_infoframe frame;
		struct i2c_client *client = v4l2_get_subdevdata(sd);

		if (adv76xx_read_infoframe(sd, i, &frame))
			return;
		hdmi_infoframe_log(KERN_INFO, &client->dev, &frame);
	}
}