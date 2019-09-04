#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_config {int dummy; } ;
struct soc_camera_subdev_desc {int (* set_bus_param ) (struct soc_camera_subdev_desc*,int) ;} ;
struct mt9m001 {TYPE_1__* fmt; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {unsigned int bits_per_sample; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client const*) ; 
 TYPE_2__* soc_mbus_get_fmtdesc (int /*<<< orphan*/ ) ; 
 int stub1 (struct soc_camera_subdev_desc*,int) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client const*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m001_s_mbus_config(struct v4l2_subdev *sd,
				const struct v4l2_mbus_config *cfg)
{
	const struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	unsigned int bps = soc_mbus_get_fmtdesc(mt9m001->fmt->code)->bits_per_sample;

	if (ssdd->set_bus_param)
		return ssdd->set_bus_param(ssdd, 1 << (bps - 1));

	/*
	 * Without board specific bus width settings we only support the
	 * sensors native bus width
	 */
	return bps == 10 ? 0 : -EINVAL;
}