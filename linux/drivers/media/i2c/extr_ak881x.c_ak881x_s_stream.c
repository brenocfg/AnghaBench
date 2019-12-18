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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct ak881x {TYPE_1__* pdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int AK881X_COMPONENT ; 
 int /*<<< orphan*/  AK881X_DAC_MODE ; 
 int /*<<< orphan*/  AK881X_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct ak881x* to_ak881x (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ak881x_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ak881x *ak881x = to_ak881x(client);

	if (enable) {
		u8 dac;
		/* For colour-bar testing set bit 6 of AK881X_VIDEO_PROCESS1 */
		/* Default: composite output */
		if (ak881x->pdata->flags & AK881X_COMPONENT)
			dac = 3;
		else
			dac = 4;
		/* Turn on the DAC(s) */
		reg_write(client, AK881X_DAC_MODE, dac);
		dev_dbg(&client->dev, "chip status 0x%x\n",
			reg_read(client, AK881X_STATUS));
	} else {
		/* ...and clear bit 6 of AK881X_VIDEO_PROCESS1 here */
		reg_write(client, AK881X_DAC_MODE, 0);
		dev_dbg(&client->dev, "chip status 0x%x\n",
			reg_read(client, AK881X_STATUS));
	}

	return 0;
}