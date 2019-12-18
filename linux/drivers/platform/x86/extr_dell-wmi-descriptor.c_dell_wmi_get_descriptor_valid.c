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

/* Variables and functions */
 int /*<<< orphan*/  DELL_WMI_DESCRIPTOR_GUID ; 
 int ENODEV ; 
 int descriptor_valid ; 
 int /*<<< orphan*/  wmi_has_guid (int /*<<< orphan*/ ) ; 

int dell_wmi_get_descriptor_valid(void)
{
	if (!wmi_has_guid(DELL_WMI_DESCRIPTOR_GUID))
		return -ENODEV;

	return descriptor_valid;
}