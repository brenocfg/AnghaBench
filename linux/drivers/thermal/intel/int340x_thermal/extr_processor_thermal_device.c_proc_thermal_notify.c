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
struct proc_thermal_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  int340x_zone; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
#define  PROC_POWER_CAPABILITY_CHANGED 128 
 int /*<<< orphan*/  THERMAL_DEVICE_POWER_CAPABILITY_CHANGED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  int340x_thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_thermal_read_ppcc (struct proc_thermal_device*) ; 

__attribute__((used)) static void proc_thermal_notify(acpi_handle handle, u32 event, void *data)
{
	struct proc_thermal_device *proc_priv = data;

	if (!proc_priv)
		return;

	switch (event) {
	case PROC_POWER_CAPABILITY_CHANGED:
		proc_thermal_read_ppcc(proc_priv);
		int340x_thermal_zone_device_update(proc_priv->int340x_zone,
				THERMAL_DEVICE_POWER_CAPABILITY_CHANGED);
		break;
	default:
		dev_dbg(proc_priv->dev, "Unsupported event [0x%x]\n", event);
		break;
	}
}