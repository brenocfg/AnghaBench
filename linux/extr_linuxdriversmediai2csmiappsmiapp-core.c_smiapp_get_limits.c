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
typedef  int /*<<< orphan*/  u32 ;
struct smiapp_sensor {int /*<<< orphan*/ * limits; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  what; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smiapp_read (struct smiapp_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* smiapp_reg_limits ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_get_limits(struct smiapp_sensor *sensor, int const *limit,
			     unsigned int n)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	unsigned int i;
	u32 val;
	int rval;

	for (i = 0; i < n; i++) {
		rval = smiapp_read(
			sensor, smiapp_reg_limits[limit[i]].addr, &val);
		if (rval)
			return rval;
		sensor->limits[limit[i]] = val;
		dev_dbg(&client->dev, "0x%8.8x \"%s\" = %u, 0x%x\n",
			smiapp_reg_limits[limit[i]].addr,
			smiapp_reg_limits[limit[i]].what, val, val);
	}

	return 0;
}