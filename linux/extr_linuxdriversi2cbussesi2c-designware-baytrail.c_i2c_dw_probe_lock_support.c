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
struct dw_i2c_dev {int pm_disabled; int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  release_lock; int /*<<< orphan*/  acquire_lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  baytrail_i2c_acquire ; 
 int /*<<< orphan*/  baytrail_i2c_release ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iosf_mbi_available () ; 
 int /*<<< orphan*/  pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int i2c_dw_probe_lock_support(struct dw_i2c_dev *dev)
{
	acpi_status status;
	unsigned long long shared_host = 0;
	acpi_handle handle;

	if (!dev || !dev->dev)
		return 0;

	handle = ACPI_HANDLE(dev->dev);
	if (!handle)
		return 0;

	status = acpi_evaluate_integer(handle, "_SEM", NULL, &shared_host);
	if (ACPI_FAILURE(status))
		return 0;

	if (!shared_host)
		return 0;

	if (!iosf_mbi_available())
		return -EPROBE_DEFER;

	dev_info(dev->dev, "I2C bus managed by PUNIT\n");
	dev->acquire_lock = baytrail_i2c_acquire;
	dev->release_lock = baytrail_i2c_release;
	dev->pm_disabled = true;

	pm_qos_add_request(&dev->pm_qos, PM_QOS_CPU_DMA_LATENCY,
			   PM_QOS_DEFAULT_VALUE);

	return 0;
}