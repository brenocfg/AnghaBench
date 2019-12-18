#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fan_ctrl_status_undef; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  TPACPI_DBG_FAN ; 
#define  TPACPI_FAN_WR_ACPI_FANS 130 
#define  TPACPI_FAN_WR_ACPI_SFAN 129 
#define  TPACPI_FAN_WR_TPEC 128 
 int TP_EC_FAN_AUTO ; 
 int TP_EC_FAN_FULLSPEED ; 
 int /*<<< orphan*/  acpi_ec_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int fan_control_access_mode ; 
 int /*<<< orphan*/  fan_control_allowed ; 
 int /*<<< orphan*/  fan_status_offset ; 
 int /*<<< orphan*/  sfan_handle ; 
 TYPE_1__ tp_features ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int fan_set_level(int level)
{
	if (!fan_control_allowed)
		return -EPERM;

	switch (fan_control_access_mode) {
	case TPACPI_FAN_WR_ACPI_SFAN:
		if (level >= 0 && level <= 7) {
			if (!acpi_evalf(sfan_handle, NULL, NULL, "vd", level))
				return -EIO;
		} else
			return -EINVAL;
		break;

	case TPACPI_FAN_WR_ACPI_FANS:
	case TPACPI_FAN_WR_TPEC:
		if (!(level & TP_EC_FAN_AUTO) &&
		    !(level & TP_EC_FAN_FULLSPEED) &&
		    ((level < 0) || (level > 7)))
			return -EINVAL;

		/* safety net should the EC not support AUTO
		 * or FULLSPEED mode bits and just ignore them */
		if (level & TP_EC_FAN_FULLSPEED)
			level |= 7;	/* safety min speed 7 */
		else if (level & TP_EC_FAN_AUTO)
			level |= 4;	/* safety min speed 4 */

		if (!acpi_ec_write(fan_status_offset, level))
			return -EIO;
		else
			tp_features.fan_ctrl_status_undef = 0;
		break;

	default:
		return -ENXIO;
	}

	vdbg_printk(TPACPI_DBG_FAN,
		"fan control: set fan control register to 0x%02x\n", level);
	return 0;
}