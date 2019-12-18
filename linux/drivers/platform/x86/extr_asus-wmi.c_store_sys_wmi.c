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
typedef  int /*<<< orphan*/  u32 ;
struct asus_wmi {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int) ; 
 int asus_wmi_set_devstate (int,int,int /*<<< orphan*/ *) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t store_sys_wmi(struct asus_wmi *asus, int devid,
			     const char *buf, size_t count)
{
	u32 retval;
	int err, value;

	value = asus_wmi_get_devstate_simple(asus, devid);
	if (value < 0)
		return value;

	err = kstrtoint(buf, 0, &value);
	if (err)
		return err;

	err = asus_wmi_set_devstate(devid, value, &retval);
	if (err < 0)
		return err;

	return count;
}