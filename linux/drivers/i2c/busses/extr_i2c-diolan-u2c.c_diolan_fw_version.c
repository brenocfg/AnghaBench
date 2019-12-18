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
struct i2c_diolan_u2c {scalar_t__* ibuffer; TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_FW_VERSION ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int diolan_usb_cmd (struct i2c_diolan_u2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void diolan_fw_version(struct i2c_diolan_u2c *dev)
{
	int ret;

	ret = diolan_usb_cmd(dev, CMD_GET_FW_VERSION, true);
	if (ret >= 2)
		dev_info(&dev->interface->dev,
			 "Diolan U2C firmware version %u.%u\n",
			 (unsigned int)dev->ibuffer[0],
			 (unsigned int)dev->ibuffer[1]);
}