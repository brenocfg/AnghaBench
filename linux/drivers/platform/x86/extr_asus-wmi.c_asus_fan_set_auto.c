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
struct asus_wmi {int fan_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_CPU_FAN_CTRL ; 
 int EIO ; 
 int ENXIO ; 
#define  FAN_TYPE_AGFN 129 
#define  FAN_TYPE_SPEC83 128 
 int asus_agfn_fan_speed_write (struct asus_wmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int asus_wmi_set_devstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int asus_fan_set_auto(struct asus_wmi *asus)
{
	int status;
	u32 retval;

	switch (asus->fan_type) {
	case FAN_TYPE_SPEC83:
		status = asus_wmi_set_devstate(ASUS_WMI_DEVID_CPU_FAN_CTRL,
					       0, &retval);
		if (status)
			return status;

		if (retval != 1)
			return -EIO;
		break;

	case FAN_TYPE_AGFN:
		status = asus_agfn_fan_speed_write(asus, 0, NULL);
		if (status)
			return -ENXIO;
		break;

	default:
		return -ENXIO;
	}


	return 0;
}