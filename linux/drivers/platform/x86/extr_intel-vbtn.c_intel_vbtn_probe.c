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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct intel_vbtn_priv {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_ec_mark_gpe_for_wake () ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  detect_tablet_mode (struct platform_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct intel_vbtn_priv*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct intel_vbtn_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int intel_vbtn_input_setup (struct platform_device*) ; 
 int /*<<< orphan*/  notify_handler ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int intel_vbtn_probe(struct platform_device *device)
{
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	struct intel_vbtn_priv *priv;
	acpi_status status;
	int err;

	status = acpi_evaluate_object(handle, "VBDL", NULL, NULL);
	if (ACPI_FAILURE(status)) {
		dev_warn(&device->dev, "failed to read Intel Virtual Button driver\n");
		return -ENODEV;
	}

	priv = devm_kzalloc(&device->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	dev_set_drvdata(&device->dev, priv);

	err = intel_vbtn_input_setup(device);
	if (err) {
		pr_err("Failed to setup Intel Virtual Button\n");
		return err;
	}

	detect_tablet_mode(device);

	status = acpi_install_notify_handler(handle,
					     ACPI_DEVICE_NOTIFY,
					     notify_handler,
					     device);
	if (ACPI_FAILURE(status))
		return -EBUSY;

	device_init_wakeup(&device->dev, true);
	/*
	 * In order for system wakeup to work, the EC GPE has to be marked as
	 * a wakeup one, so do that here (this setting will persist, but it has
	 * no effect until the wakeup mask is set for the EC GPE).
	 */
	acpi_ec_mark_gpe_for_wake();
	return 0;
}