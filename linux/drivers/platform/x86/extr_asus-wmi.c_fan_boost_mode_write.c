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
typedef  int u32 ;
struct asus_wmi {int /*<<< orphan*/  fan_boost_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASUS_WMI_DEVID_FAN_BOOST_MODE ; 
 int EIO ; 
 int asus_wmi_set_devstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int fan_boost_mode_write(struct asus_wmi *asus)
{
	int err;
	u8 value;
	u32 retval;

	value = asus->fan_boost_mode;

	pr_info("Set fan boost mode: %u\n", value);
	err = asus_wmi_set_devstate(ASUS_WMI_DEVID_FAN_BOOST_MODE, value,
				    &retval);
	if (err) {
		pr_warn("Failed to set fan boost mode: %d\n", err);
		return err;
	}

	if (retval != 1) {
		pr_warn("Failed to set fan boost mode (retval): 0x%x\n",
			retval);
		return -EIO;
	}

	return 0;
}