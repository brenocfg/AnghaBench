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
typedef  int u32 ;
struct smiapp_sensor {TYPE_2__* hwcfg; TYPE_1__* src; } ;
struct i2c_client {int addr; } ;
struct TYPE_4__ {int i2c_addr_dfl; int i2c_addr_alt; } ;
struct TYPE_3__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SMIAPP_REG_U8_CCI_ADDRESS_CONTROL ; 
 int smiapp_read (struct smiapp_sensor*,int /*<<< orphan*/ ,int*) ; 
 int smiapp_write (struct smiapp_sensor*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_change_cci_addr(struct smiapp_sensor *sensor)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	int rval;
	u32 val;

	client->addr = sensor->hwcfg->i2c_addr_dfl;

	rval = smiapp_write(sensor,
			    SMIAPP_REG_U8_CCI_ADDRESS_CONTROL,
			    sensor->hwcfg->i2c_addr_alt << 1);
	if (rval)
		return rval;

	client->addr = sensor->hwcfg->i2c_addr_alt;

	/* verify addr change went ok */
	rval = smiapp_read(sensor, SMIAPP_REG_U8_CCI_ADDRESS_CONTROL, &val);
	if (rval)
		return rval;

	if (val != sensor->hwcfg->i2c_addr_alt << 1)
		return -ENODEV;

	return 0;
}