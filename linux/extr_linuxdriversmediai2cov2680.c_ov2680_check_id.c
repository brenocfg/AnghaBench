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
typedef  scalar_t__ u32 ;
struct ov2680_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OV2680_CHIP_ID ; 
 int /*<<< orphan*/  OV2680_REG_CHIP_ID_HIGH ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  ov2680_power_on (struct ov2680_dev*) ; 
 int ov2680_read_reg16 (struct ov2680_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct device* ov2680_to_dev (struct ov2680_dev*) ; 

__attribute__((used)) static int ov2680_check_id(struct ov2680_dev *sensor)
{
	struct device *dev = ov2680_to_dev(sensor);
	u32 chip_id;
	int ret;

	ov2680_power_on(sensor);

	ret = ov2680_read_reg16(sensor, OV2680_REG_CHIP_ID_HIGH, &chip_id);
	if (ret < 0) {
		dev_err(dev, "failed to read chip id high\n");
		return -ENODEV;
	}

	if (chip_id != OV2680_CHIP_ID) {
		dev_err(dev, "chip id: 0x%04x does not match expected 0x%04x\n",
			chip_id, OV2680_CHIP_ID);
		return -ENODEV;
	}

	return 0;
}