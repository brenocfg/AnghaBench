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
typedef  int u32 ;
struct device {int dummy; } ;
struct at24_platform_data {int flags; int byte_len; int page_size; } ;

/* Variables and functions */
 int AT24_FLAG_ADDR16 ; 
 int AT24_FLAG_NO_RDROL ; 
 int AT24_FLAG_READONLY ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 scalar_t__ device_property_present (struct device*,char*) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 

__attribute__((used)) static void at24_properties_to_pdata(struct device *dev,
				     struct at24_platform_data *chip)
{
	int err;
	u32 val;

	if (device_property_present(dev, "read-only"))
		chip->flags |= AT24_FLAG_READONLY;
	if (device_property_present(dev, "no-read-rollover"))
		chip->flags |= AT24_FLAG_NO_RDROL;

	err = device_property_read_u32(dev, "address-width", &val);
	if (!err) {
		switch (val) {
		case 8:
			if (chip->flags & AT24_FLAG_ADDR16)
				dev_warn(dev, "Override address width to be 8, while default is 16\n");
			chip->flags &= ~AT24_FLAG_ADDR16;
			break;
		case 16:
			chip->flags |= AT24_FLAG_ADDR16;
			break;
		default:
			dev_warn(dev, "Bad \"address-width\" property: %u\n",
				 val);
		}
	}

	err = device_property_read_u32(dev, "size", &val);
	if (!err)
		chip->byte_len = val;

	err = device_property_read_u32(dev, "pagesize", &val);
	if (!err) {
		chip->page_size = val;
	} else {
		/*
		 * This is slow, but we can't know all eeproms, so we better
		 * play safe. Specifying custom eeprom-types via platform_data
		 * is recommended anyhow.
		 */
		chip->page_size = 1;
	}
}