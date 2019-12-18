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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  THRESHOLD_STOP ; 
 int /*<<< orphan*/  tpacpi_battery_show (int /*<<< orphan*/ ,struct device*,char*) ; 

__attribute__((used)) static ssize_t charge_stop_threshold_show(struct device *device,
				struct device_attribute *attr,
				char *buf)
{
	return tpacpi_battery_show(THRESHOLD_STOP, device, buf);
}