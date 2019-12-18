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
struct intel_hid_priv {int /*<<< orphan*/  array; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  INTEL_HID_DSM_BTNE_FN ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 struct intel_hid_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  intel_hid_execute_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void intel_button_array_enable(struct device *device, bool enable)
{
	struct intel_hid_priv *priv = dev_get_drvdata(device);
	acpi_handle handle = ACPI_HANDLE(device);
	unsigned long long button_cap;
	acpi_status status;

	if (!priv->array)
		return;

	/* Query supported platform features */
	status = acpi_evaluate_integer(handle, "BTNC", NULL, &button_cap);
	if (ACPI_FAILURE(status)) {
		dev_warn(device, "failed to get button capability\n");
		return;
	}

	/* Enable|disable features - power button is always enabled */
	if (!intel_hid_execute_method(handle, INTEL_HID_DSM_BTNE_FN,
				      enable ? button_cap : 1))
		dev_warn(device, "failed to set button capability\n");
}