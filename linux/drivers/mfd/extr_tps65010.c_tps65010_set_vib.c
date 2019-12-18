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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int /*<<< orphan*/  TPS_VDCDC2 ; 
 unsigned int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* the_tps ; 

int tps65010_set_vib(unsigned value)
{
	int	 status;
	unsigned vdcdc2;

	if (!the_tps)
		return -ENODEV;

	mutex_lock(&the_tps->lock);

	vdcdc2 = i2c_smbus_read_byte_data(the_tps->client, TPS_VDCDC2);
	vdcdc2 &= ~(1 << 1);
	if (value)
		vdcdc2 |= (1 << 1);
	status = i2c_smbus_write_byte_data(the_tps->client,
		TPS_VDCDC2, vdcdc2);

	pr_debug("%s: vibrator %s\n", DRIVER_NAME, value ? "on" : "off");

	mutex_unlock(&the_tps->lock);
	return status;
}