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
struct asus_wmi {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int asus_wmi_get_devstate_simple (struct asus_wmi*,int) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_sys_wmi(struct asus_wmi *asus, int devid, char *buf)
{
	int value = asus_wmi_get_devstate_simple(asus, devid);

	if (value < 0)
		return value;

	return sprintf(buf, "%d\n", value);
}