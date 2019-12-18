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
typedef  int u8 ;
struct pmbus_driver_info {int /*<<< orphan*/  vrm_version; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMBUS_VOUT_MODE ; 
 scalar_t__ pmbus_check_byte_register (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vr12 ; 
 int /*<<< orphan*/  vr13 ; 

__attribute__((used)) static int pxe1610_identify(struct i2c_client *client,
			     struct pmbus_driver_info *info)
{
	if (pmbus_check_byte_register(client, 0, PMBUS_VOUT_MODE)) {
		u8 vout_mode;
		int ret;

		/* Read the register with VOUT scaling value.*/
		ret = pmbus_read_byte_data(client, 0, PMBUS_VOUT_MODE);
		if (ret < 0)
			return ret;

		vout_mode = ret & GENMASK(4, 0);

		switch (vout_mode) {
		case 1:
			info->vrm_version = vr12;
			break;
		case 2:
			info->vrm_version = vr13;
			break;
		default:
			return -ENODEV;
		}
	}

	return 0;
}