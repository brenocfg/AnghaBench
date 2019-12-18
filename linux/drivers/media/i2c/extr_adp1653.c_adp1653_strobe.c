#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct adp1653_flash {TYPE_1__* flash_intensity; TYPE_3__* led_mode; TYPE_2__* indicator_intensity; int /*<<< orphan*/  subdev; } ;
struct TYPE_6__ {scalar_t__ val; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int ADP1653_FLASH_INTENSITY_mA_TO_REG (int /*<<< orphan*/ ) ; 
 int ADP1653_INDICATOR_INTENSITY_uA_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADP1653_REG_OUT_SEL ; 
 int ADP1653_REG_OUT_SEL_HPLED_SHIFT ; 
 int ADP1653_REG_OUT_SEL_ILED_SHIFT ; 
 int /*<<< orphan*/  ADP1653_REG_SW_STROBE ; 
 int ADP1653_REG_SW_STROBE_SW_STROBE ; 
 int EBUSY ; 
 scalar_t__ V4L2_FLASH_LED_MODE_FLASH ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp1653_strobe(struct adp1653_flash *flash, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(&flash->subdev);
	u8 out_sel = ADP1653_INDICATOR_INTENSITY_uA_TO_REG(
		flash->indicator_intensity->val)
		<< ADP1653_REG_OUT_SEL_ILED_SHIFT;
	int rval;

	if (flash->led_mode->val != V4L2_FLASH_LED_MODE_FLASH)
		return -EBUSY;

	if (!enable)
		return i2c_smbus_write_byte_data(client, ADP1653_REG_OUT_SEL,
						 out_sel);

	out_sel |= ADP1653_FLASH_INTENSITY_mA_TO_REG(
		flash->flash_intensity->val)
		<< ADP1653_REG_OUT_SEL_HPLED_SHIFT;
	rval = i2c_smbus_write_byte_data(client, ADP1653_REG_OUT_SEL, out_sel);
	if (rval)
		return rval;

	/* Software strobe using i2c */
	rval = i2c_smbus_write_byte_data(client, ADP1653_REG_SW_STROBE,
		ADP1653_REG_SW_STROBE_SW_STROBE);
	if (rval)
		return rval;
	return i2c_smbus_write_byte_data(client, ADP1653_REG_SW_STROBE, 0);
}