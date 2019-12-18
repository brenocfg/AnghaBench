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
struct intel_hid_priv {scalar_t__ array; } ;
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
 int /*<<< orphan*/  INTEL_HID_DSM_BTNL_FN ; 
 int /*<<< orphan*/  INTEL_HID_DSM_HDMM_FN ; 
 int /*<<< orphan*/  acpi_ec_mark_gpe_for_wake () ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ button_array_present (struct platform_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct intel_hid_priv*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct intel_hid_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_button_array_enable (int /*<<< orphan*/ *,int) ; 
 int intel_button_array_input_setup (struct platform_device*) ; 
 int /*<<< orphan*/  intel_hid_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  intel_hid_init_dsm (int /*<<< orphan*/ ) ; 
 int intel_hid_input_setup (struct platform_device*) ; 
 int intel_hid_set_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify_handler ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int intel_hid_probe(struct platform_device *device)
{
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	unsigned long long mode;
	struct intel_hid_priv *priv;
	acpi_status status;
	int err;

	intel_hid_init_dsm(handle);

	if (!intel_hid_evaluate_method(handle, INTEL_HID_DSM_HDMM_FN, &mode)) {
		dev_warn(&device->dev, "failed to read mode\n");
		return -ENODEV;
	}

	if (mode != 0) {
		/*
		 * This driver only implements "simple" mode.  There appear
		 * to be no other modes, but we should be paranoid and check
		 * for compatibility.
		 */
		dev_info(&device->dev, "platform is not in simple mode\n");
		return -ENODEV;
	}

	priv = devm_kzalloc(&device->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	dev_set_drvdata(&device->dev, priv);

	err = intel_hid_input_setup(device);
	if (err) {
		pr_err("Failed to setup Intel HID hotkeys\n");
		return err;
	}

	/* Setup 5 button array */
	if (button_array_present(device)) {
		dev_info(&device->dev, "platform supports 5 button array\n");
		err = intel_button_array_input_setup(device);
		if (err)
			pr_err("Failed to setup Intel 5 button array hotkeys\n");
	}

	status = acpi_install_notify_handler(handle,
					     ACPI_DEVICE_NOTIFY,
					     notify_handler,
					     device);
	if (ACPI_FAILURE(status))
		return -EBUSY;

	err = intel_hid_set_enable(&device->dev, true);
	if (err)
		goto err_remove_notify;

	if (priv->array) {
		unsigned long long dummy;

		intel_button_array_enable(&device->dev, true);

		/* Call button load method to enable HID power button */
		if (!intel_hid_evaluate_method(handle, INTEL_HID_DSM_BTNL_FN,
					       &dummy)) {
			dev_warn(&device->dev,
				 "failed to enable HID power button\n");
		}
	}

	device_init_wakeup(&device->dev, true);
	/*
	 * In order for system wakeup to work, the EC GPE has to be marked as
	 * a wakeup one, so do that here (this setting will persist, but it has
	 * no effect until the wakeup mask is set for the EC GPE).
	 */
	acpi_ec_mark_gpe_for_wake();
	return 0;

err_remove_notify:
	acpi_remove_notify_handler(handle, ACPI_DEVICE_NOTIFY, notify_handler);

	return err;
}