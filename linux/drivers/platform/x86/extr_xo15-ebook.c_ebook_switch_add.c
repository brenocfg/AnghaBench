#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  bustype; } ;
struct input_dev {char* name; int /*<<< orphan*/  swbit; int /*<<< orphan*/ * evbit; TYPE_2__ dev; TYPE_1__ id; int /*<<< orphan*/  phys; } ;
struct ebook_switch {int /*<<< orphan*/  phys; struct input_dev* input; } ;
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_8__ {int /*<<< orphan*/  gpe_number; int /*<<< orphan*/  gpe_device; TYPE_3__ flags; } ;
struct acpi_device {int /*<<< orphan*/  dev; TYPE_4__ wakeup; struct ebook_switch* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_SW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SW_TABLET_MODE ; 
 char* XO15_EBOOK_CLASS ; 
 int /*<<< orphan*/  XO15_EBOOK_DEVICE_NAME ; 
 int /*<<< orphan*/  XO15_EBOOK_HID ; 
 char* XO15_EBOOK_SUBCLASS ; 
 char* acpi_device_class (struct acpi_device*) ; 
 char* acpi_device_hid (struct acpi_device*) ; 
 char* acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_enable_gpe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ebook_send_state (struct acpi_device*) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct ebook_switch*) ; 
 struct ebook_switch* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ebook_switch_add(struct acpi_device *device)
{
	struct ebook_switch *button;
	struct input_dev *input;
	const char *hid = acpi_device_hid(device);
	char *name, *class;
	int error;

	button = kzalloc(sizeof(struct ebook_switch), GFP_KERNEL);
	if (!button)
		return -ENOMEM;

	device->driver_data = button;

	button->input = input = input_allocate_device();
	if (!input) {
		error = -ENOMEM;
		goto err_free_button;
	}

	name = acpi_device_name(device);
	class = acpi_device_class(device);

	if (strcmp(hid, XO15_EBOOK_HID)) {
		pr_err("Unsupported hid [%s]\n", hid);
		error = -ENODEV;
		goto err_free_input;
	}

	strcpy(name, XO15_EBOOK_DEVICE_NAME);
	sprintf(class, "%s/%s", XO15_EBOOK_CLASS, XO15_EBOOK_SUBCLASS);

	snprintf(button->phys, sizeof(button->phys), "%s/button/input0", hid);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &device->dev;

	input->evbit[0] = BIT_MASK(EV_SW);
	set_bit(SW_TABLET_MODE, input->swbit);

	error = input_register_device(input);
	if (error)
		goto err_free_input;

	ebook_send_state(device);

	if (device->wakeup.flags.valid) {
		/* Button's GPE is run-wake GPE */
		acpi_enable_gpe(device->wakeup.gpe_device,
				device->wakeup.gpe_number);
		device_set_wakeup_enable(&device->dev, true);
	}

	return 0;

 err_free_input:
	input_free_device(input);
 err_free_button:
	kfree(button);
	return error;
}