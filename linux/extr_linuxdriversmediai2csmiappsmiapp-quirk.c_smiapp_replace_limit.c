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
typedef  size_t u32 ;
struct smiapp_sensor {size_t* limits; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  what; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t) ; 
 TYPE_2__* smiapp_reg_limits ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

void smiapp_replace_limit(struct smiapp_sensor *sensor,
			  u32 limit, u32 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);

	dev_dbg(&client->dev, "quirk: 0x%8.8x \"%s\" = %d, 0x%x\n",
		smiapp_reg_limits[limit].addr,
		smiapp_reg_limits[limit].what, val, val);
	sensor->limits[limit] = val;
}