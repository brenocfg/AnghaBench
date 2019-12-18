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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 unsigned short THM_PROFILE_MAX ; 
 int /*<<< orphan*/ * snc_thermal_profiles ; 
 scalar_t__ sony_nc_thermal_mode_set (unsigned short) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t sony_nc_thermal_mode_store(struct device *dev,
		struct device_attribute *attr,
		const char *buffer, size_t count)
{
	unsigned short cmd;
	size_t len = count;

	if (count == 0)
		return -EINVAL;

	/* skip the newline if present */
	if (buffer[len - 1] == '\n')
		len--;

	for (cmd = 0; cmd < THM_PROFILE_MAX; cmd++)
		if (strncmp(buffer, snc_thermal_profiles[cmd], len) == 0)
			break;

	if (sony_nc_thermal_mode_set(cmd))
		return -EIO;

	return count;
}