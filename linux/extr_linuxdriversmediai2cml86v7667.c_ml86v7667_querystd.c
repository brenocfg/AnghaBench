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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int STATUS_HLOCK_DETECT ; 
 int STATUS_NTSCPAL ; 
 int /*<<< orphan*/  STATUS_REG ; 
 int /*<<< orphan*/  V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_STD_625_50 ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ml86v7667_querystd(struct v4l2_subdev *sd, v4l2_std_id *std)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int status;

	status = i2c_smbus_read_byte_data(client, STATUS_REG);
	if (status < 0)
		return status;

	if (status & STATUS_HLOCK_DETECT)
		*std &= status & STATUS_NTSCPAL ? V4L2_STD_625_50 : V4L2_STD_525_60;
	else
		*std = V4L2_STD_UNKNOWN;

	return 0;
}