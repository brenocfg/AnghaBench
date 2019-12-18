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
struct max14577 {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int DEVID_DEVICEID_MASK ; 
 int DEVID_DEVICEID_SHIFT ; 
 int DEVID_VENDORID_MASK ; 
 int DEVID_VENDORID_SHIFT ; 
 int /*<<< orphan*/  MAX14577_REG_DEVICEID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int max14577_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void max14577_print_dev_type(struct max14577 *max14577)
{
	u8 reg_data, vendor_id, device_id;
	int ret;

	ret = max14577_read_reg(max14577->regmap, MAX14577_REG_DEVICEID,
			&reg_data);
	if (ret) {
		dev_err(max14577->dev,
			"Failed to read DEVICEID register: %d\n", ret);
		return;
	}

	vendor_id = ((reg_data & DEVID_VENDORID_MASK) >>
				DEVID_VENDORID_SHIFT);
	device_id = ((reg_data & DEVID_DEVICEID_MASK) >>
				DEVID_DEVICEID_SHIFT);

	dev_info(max14577->dev, "Device type: %u (ID: 0x%x, vendor: 0x%x)\n",
			max14577->dev_type, device_id, vendor_id);
}