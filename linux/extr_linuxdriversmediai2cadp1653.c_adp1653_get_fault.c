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
struct i2c_client {int dummy; } ;
struct adp1653_flash {int fault; TYPE_1__* led_mode; int /*<<< orphan*/  subdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP1653_REG_FAULT ; 
 int /*<<< orphan*/  ADP1653_REG_OUT_SEL ; 
 int /*<<< orphan*/  V4L2_FLASH_LED_MODE_NONE ; 
 int adp1653_update_hw (struct adp1653_flash*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp1653_get_fault(struct adp1653_flash *flash)
{
	struct i2c_client *client = v4l2_get_subdevdata(&flash->subdev);
	int fault;
	int rval;

	fault = i2c_smbus_read_byte_data(client, ADP1653_REG_FAULT);
	if (fault < 0)
		return fault;

	flash->fault |= fault;

	if (!flash->fault)
		return 0;

	/* Clear faults. */
	rval = i2c_smbus_write_byte_data(client, ADP1653_REG_OUT_SEL, 0);
	if (rval < 0)
		return rval;

	flash->led_mode->val = V4L2_FLASH_LED_MODE_NONE;

	rval = adp1653_update_hw(flash);
	if (rval)
		return rval;

	return flash->fault;
}