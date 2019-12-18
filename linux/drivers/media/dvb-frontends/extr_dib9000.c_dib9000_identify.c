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
typedef  int u16 ;
struct i2c_device {int dummy; } ;

/* Variables and functions */
 int dib9000_i2c_read16 (struct i2c_device*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static u16 dib9000_identify(struct i2c_device *client)
{
	u16 value;

	value = dib9000_i2c_read16(client, 896);
	if (value != 0x01b3) {
		dprintk("wrong Vendor ID (0x%x)\n", value);
		return 0;
	}

	value = dib9000_i2c_read16(client, 897);
	if (value != 0x4000 && value != 0x4001 && value != 0x4002 && value != 0x4003 && value != 0x4004 && value != 0x4005) {
		dprintk("wrong Device ID (0x%x)\n", value);
		return 0;
	}

	/* protect this driver to be used with 7000PC */
	if (value == 0x4000 && dib9000_i2c_read16(client, 769) == 0x4000) {
		dprintk("this driver does not work with DiB7000PC\n");
		return 0;
	}

	switch (value) {
	case 0x4000:
		dprintk("found DiB7000MA/PA/MB/PB\n");
		break;
	case 0x4001:
		dprintk("found DiB7000HC\n");
		break;
	case 0x4002:
		dprintk("found DiB7000MC\n");
		break;
	case 0x4003:
		dprintk("found DiB9000A\n");
		break;
	case 0x4004:
		dprintk("found DiB9000H\n");
		break;
	case 0x4005:
		dprintk("found DiB9000M\n");
		break;
	}

	return value;
}