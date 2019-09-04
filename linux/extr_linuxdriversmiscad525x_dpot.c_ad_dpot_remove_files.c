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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 unsigned int F_CMD_EEP ; 
 unsigned int F_CMD_OTP ; 
 unsigned int F_CMD_TOL ; 
 int /*<<< orphan*/ * dpot_attrib_eeprom ; 
 int /*<<< orphan*/ * dpot_attrib_otp ; 
 int /*<<< orphan*/ * dpot_attrib_otp_en ; 
 int /*<<< orphan*/ * dpot_attrib_tolerance ; 
 int /*<<< orphan*/ * dpot_attrib_wipers ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ad_dpot_remove_files(struct device *dev,
		unsigned int features, unsigned int rdac)
{
	sysfs_remove_file(&dev->kobj,
		dpot_attrib_wipers[rdac]);
	if (features & F_CMD_EEP)
		sysfs_remove_file(&dev->kobj,
			dpot_attrib_eeprom[rdac]);
	if (features & F_CMD_TOL)
		sysfs_remove_file(&dev->kobj,
			dpot_attrib_tolerance[rdac]);
	if (features & F_CMD_OTP) {
		sysfs_remove_file(&dev->kobj,
			dpot_attrib_otp_en[rdac]);
		sysfs_remove_file(&dev->kobj,
			dpot_attrib_otp[rdac]);
	}
}