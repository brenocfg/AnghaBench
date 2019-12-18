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
struct ds2780_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2780_RARC_REG ; 
 int ds2780_read8 (struct ds2780_device_info*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds2780_get_capacity(struct ds2780_device_info *dev_info,
	int *capacity)
{
	int ret;
	u8 raw;

	ret = ds2780_read8(dev_info, &raw, DS2780_RARC_REG);
	if (ret < 0)
		return ret;

	*capacity = raw;
	return raw;
}