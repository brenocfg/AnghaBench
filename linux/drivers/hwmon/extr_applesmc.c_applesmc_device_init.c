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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  has_accelerometer; } ;

/* Variables and functions */
 int INIT_TIMEOUT_MSECS ; 
 scalar_t__ INIT_WAIT_MSECS ; 
 int /*<<< orphan*/  MOTION_SENSOR_KEY ; 
 int /*<<< orphan*/  applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  applesmc_write_key (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static void applesmc_device_init(void)
{
	int total;
	u8 buffer[2];

	if (!smcreg.has_accelerometer)
		return;

	for (total = INIT_TIMEOUT_MSECS; total > 0; total -= INIT_WAIT_MSECS) {
		if (!applesmc_read_key(MOTION_SENSOR_KEY, buffer, 2) &&
				(buffer[0] != 0x00 || buffer[1] != 0x00))
			return;
		buffer[0] = 0xe0;
		buffer[1] = 0x00;
		applesmc_write_key(MOTION_SENSOR_KEY, buffer, 2);
		msleep(INIT_WAIT_MSECS);
	}

	pr_warn("failed to init the device\n");
}