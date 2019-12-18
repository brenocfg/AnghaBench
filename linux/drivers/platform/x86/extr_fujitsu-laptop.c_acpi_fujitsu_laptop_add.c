#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fujitsu_laptop {scalar_t__ flags_supported; int /*<<< orphan*/  fifo; scalar_t__ flags_state; int /*<<< orphan*/  fifo_lock; } ;
struct acpi_device {int /*<<< orphan*/  handle; struct fujitsu_laptop* driver_data; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_2__* bl_device; } ;
struct TYPE_4__ {int /*<<< orphan*/  power; } ;
struct TYPE_5__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUJITSU_CLASS ; 
 int /*<<< orphan*/  ACPI_FUJITSU_LAPTOP_DEVICE_NAME ; 
 scalar_t__ BACKLIGHT_OFF ; 
 int BACKLIGHT_PARAM_POWER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_POWERDOWN ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  FUNC_BACKLIGHT ; 
 int /*<<< orphan*/  FUNC_BUTTONS ; 
 int /*<<< orphan*/  FUNC_FLAGS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_HOTKEY_RINGBUFFER_SIZE ; 
 int RINGBUFFERSIZE ; 
 scalar_t__ UNSUPPORTED_CMD ; 
 int /*<<< orphan*/  WARN_ONCE (struct acpi_device*,char*) ; 
 scalar_t__ acpi_backlight_vendor ; 
 int /*<<< orphan*/  acpi_device_bid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int acpi_fujitsu_laptop_input_setup (struct acpi_device*) ; 
 int acpi_fujitsu_laptop_leds_register (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  acpi_handle_info (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ acpi_video_get_backlight_type () ; 
 scalar_t__ call_fext_func (struct acpi_device*,int /*<<< orphan*/ ,int,int,int) ; 
 struct fujitsu_laptop* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct acpi_device* fext ; 
 TYPE_3__* fujitsu_bl ; 
 int fujitsu_laptop_platform_add (struct acpi_device*) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_fujitsu_laptop_add(struct acpi_device *device)
{
	struct fujitsu_laptop *priv;
	int ret, i = 0;

	priv = devm_kzalloc(&device->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	WARN_ONCE(fext, "More than one FUJ02E3 ACPI device was found.  Driver may not work as intended.");
	fext = device;

	strcpy(acpi_device_name(device), ACPI_FUJITSU_LAPTOP_DEVICE_NAME);
	strcpy(acpi_device_class(device), ACPI_FUJITSU_CLASS);
	device->driver_data = priv;

	/* kfifo */
	spin_lock_init(&priv->fifo_lock);
	ret = kfifo_alloc(&priv->fifo, RINGBUFFERSIZE * sizeof(int),
			  GFP_KERNEL);
	if (ret)
		return ret;

	pr_info("ACPI: %s [%s]\n",
		acpi_device_name(device), acpi_device_bid(device));

	while (call_fext_func(device, FUNC_BUTTONS, 0x1, 0x0, 0x0) != 0 &&
	       i++ < MAX_HOTKEY_RINGBUFFER_SIZE)
		; /* No action, result is discarded */
	acpi_handle_debug(device->handle, "Discarded %i ringbuffer entries\n",
			  i);

	priv->flags_supported = call_fext_func(device, FUNC_FLAGS, 0x0, 0x0,
					       0x0);

	/* Make sure our bitmask of supported functions is cleared if the
	   RFKILL function block is not implemented, like on the S7020. */
	if (priv->flags_supported == UNSUPPORTED_CMD)
		priv->flags_supported = 0;

	if (priv->flags_supported)
		priv->flags_state = call_fext_func(device, FUNC_FLAGS, 0x4, 0x0,
						   0x0);

	/* Suspect this is a keymap of the application panel, print it */
	acpi_handle_info(device->handle, "BTNI: [0x%x]\n",
			 call_fext_func(device, FUNC_BUTTONS, 0x0, 0x0, 0x0));

	/* Sync backlight power status */
	if (fujitsu_bl && fujitsu_bl->bl_device &&
	    acpi_video_get_backlight_type() == acpi_backlight_vendor) {
		if (call_fext_func(fext, FUNC_BACKLIGHT, 0x2,
				   BACKLIGHT_PARAM_POWER, 0x0) == BACKLIGHT_OFF)
			fujitsu_bl->bl_device->props.power = FB_BLANK_POWERDOWN;
		else
			fujitsu_bl->bl_device->props.power = FB_BLANK_UNBLANK;
	}

	ret = acpi_fujitsu_laptop_input_setup(device);
	if (ret)
		goto err_free_fifo;

	ret = acpi_fujitsu_laptop_leds_register(device);
	if (ret)
		goto err_free_fifo;

	ret = fujitsu_laptop_platform_add(device);
	if (ret)
		goto err_free_fifo;

	return 0;

err_free_fifo:
	kfifo_free(&priv->fifo);

	return ret;
}