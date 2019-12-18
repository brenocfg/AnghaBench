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
struct rx51_device_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel_vbat; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int rx51_battery_read_adc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rx51_battery_read_voltage(struct rx51_device_info *di)
{
	int voltage = rx51_battery_read_adc(di->channel_vbat);

	if (voltage < 0) {
		dev_err(di->dev, "Could not read ADC: %d\n", voltage);
		return voltage;
	}

	return 1000 * (10000 * voltage / 1705);
}