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
struct rj54n1_pdata {int ioctl_high; } ;
struct rj54n1 {int /*<<< orphan*/  subdev; int /*<<< orphan*/  hdl; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RJ54N1_DEV_CODE ; 
 int /*<<< orphan*/  RJ54N1_DEV_CODE2 ; 
 int /*<<< orphan*/  RJ54N1_IOC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int rj54n1_s_power (int /*<<< orphan*/ *,int) ; 
 struct rj54n1* to_rj54n1 (struct i2c_client*) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rj54n1_video_probe(struct i2c_client *client,
			      struct rj54n1_pdata *priv)
{
	struct rj54n1 *rj54n1 = to_rj54n1(client);
	int data1, data2;
	int ret;

	ret = rj54n1_s_power(&rj54n1->subdev, 1);
	if (ret < 0)
		return ret;

	/* Read out the chip version register */
	data1 = reg_read(client, RJ54N1_DEV_CODE);
	data2 = reg_read(client, RJ54N1_DEV_CODE2);

	if (data1 != 0x51 || data2 != 0x10) {
		ret = -ENODEV;
		dev_info(&client->dev, "No RJ54N1CB0C found, read 0x%x:0x%x\n",
			 data1, data2);
		goto done;
	}

	/* Configure IOCTL polarity from the platform data: 0 or 1 << 7. */
	ret = reg_write(client, RJ54N1_IOC, priv->ioctl_high << 7);
	if (ret < 0)
		goto done;

	dev_info(&client->dev, "Detected a RJ54N1CB0C chip ID 0x%x:0x%x\n",
		 data1, data2);

	ret = v4l2_ctrl_handler_setup(&rj54n1->hdl);

done:
	rj54n1_s_power(&rj54n1->subdev, 0);
	return ret;
}