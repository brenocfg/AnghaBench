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
typedef  int /*<<< orphan*/  u8 ;
struct ds2781_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2781_RSNSP ; 
 int ds2781_save_eeprom (struct ds2781_device_info*,int /*<<< orphan*/ ) ; 
 int ds2781_write (struct ds2781_device_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ds2781_set_sense_register(struct ds2781_device_info *dev_info,
	u8 conductance)
{
	int ret;

	ret = ds2781_write(dev_info, &conductance,
				DS2781_RSNSP, sizeof(u8));
	if (ret < 0)
		return ret;

	return ds2781_save_eeprom(dev_info, DS2781_RSNSP);
}