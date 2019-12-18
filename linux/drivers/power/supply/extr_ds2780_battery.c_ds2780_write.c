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
struct ds2780_device_info {int dummy; } ;

/* Variables and functions */
 int ds2780_battery_io (struct ds2780_device_info*,int /*<<< orphan*/ *,int,size_t,int) ; 

__attribute__((used)) static inline int ds2780_write(struct ds2780_device_info *dev_info, u8 *val,
	int addr, size_t count)
{
	return ds2780_battery_io(dev_info, val, addr, count, 1);
}