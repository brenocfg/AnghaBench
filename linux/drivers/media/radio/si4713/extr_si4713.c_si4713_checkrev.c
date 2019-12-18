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
typedef  scalar_t__ u8 ;
struct si4713_device {int /*<<< orphan*/  sd; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int EINVAL ; 
 int /*<<< orphan*/  SI4713_CMD_GET_REV ; 
 int SI4713_GETREV_NRESP ; 
 scalar_t__ SI4713_PRODUCT_NUMBER ; 
 int si4713_send_command (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_checkrev(struct si4713_device *sdev)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	int rval;
	u8 resp[SI4713_GETREV_NRESP];

	rval = si4713_send_command(sdev, SI4713_CMD_GET_REV,
					NULL, 0,
					resp, ARRAY_SIZE(resp),
					DEFAULT_TIMEOUT);

	if (rval < 0)
		return rval;

	if (resp[1] == SI4713_PRODUCT_NUMBER) {
		v4l2_info(&sdev->sd, "chip found @ 0x%02x (%s)\n",
				client->addr << 1, client->adapter->name);
	} else {
		v4l2_err(&sdev->sd, "Invalid product number 0x%X\n", resp[1]);
		rval = -EINVAL;
	}
	return rval;
}