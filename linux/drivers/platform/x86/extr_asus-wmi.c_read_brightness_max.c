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
struct asus_wmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_BRIGHTNESS ; 
 int ASUS_WMI_DSTS_MAX_BRIGTH_MASK ; 
 int ENODEV ; 
 int asus_wmi_get_devstate (struct asus_wmi*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int read_brightness_max(struct asus_wmi *asus)
{
	u32 retval;
	int err;

	err = asus_wmi_get_devstate(asus, ASUS_WMI_DEVID_BRIGHTNESS, &retval);
	if (err < 0)
		return err;

	retval = retval & ASUS_WMI_DSTS_MAX_BRIGTH_MASK;
	retval >>= 8;

	if (!retval)
		return -ENODEV;

	return retval;
}