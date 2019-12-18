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
typedef  int u32 ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct pnp_device_id {int dummy; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;
struct backlight_properties {scalar_t__ max_brightness; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct apple_gmux_data {scalar_t__ iostart; scalar_t__ iolen; int indexed; int gpe; int external_switchable; int /*<<< orphan*/  dhandle; int /*<<< orphan*/  powerchange_done; int /*<<< orphan*/  power_state; struct backlight_device* bdev; int /*<<< orphan*/  index_lock; } ;
typedef  int /*<<< orphan*/  props ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DEVICE_NOTIFY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BACKLIGHT_PLATFORM ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GMUX_MAX_BRIGHTNESS ; 
 scalar_t__ GMUX_MIN_IO_LEN ; 
 int /*<<< orphan*/  GMUX_PORT_MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  GMUX_PORT_SWITCH_EXTERNAL ; 
 int /*<<< orphan*/  GMUX_PORT_VERSION_MAJOR ; 
 int /*<<< orphan*/  GMUX_PORT_VERSION_MINOR ; 
 int /*<<< orphan*/  GMUX_PORT_VERSION_RELEASE ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int PTR_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  VGA_SWITCHEROO_CAN_SWITCH_DDC ; 
 int /*<<< orphan*/  VGA_SWITCHEROO_NEEDS_EDP_CONFIG ; 
 int /*<<< orphan*/  VGA_SWITCHEROO_ON ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  acpi_backlight_vendor ; 
 int /*<<< orphan*/  acpi_disable_gpe (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acpi_enable_gpe (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_format_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pnp_dev*) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_video_set_dmi_backlight_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apple_bl_unregister () ; 
 struct apple_gmux_data* apple_gmux_data ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ *,struct apple_gmux_data*,int /*<<< orphan*/ *,struct backlight_properties*) ; 
 int /*<<< orphan*/  backlight_device_unregister (struct backlight_device*) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmux_bl_ops ; 
 int /*<<< orphan*/  gmux_disable_interrupts (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_enable_interrupts (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_get_brightness (struct backlight_device*) ; 
 int /*<<< orphan*/  gmux_handler_classic ; 
 int /*<<< orphan*/  gmux_handler_indexed ; 
 scalar_t__ gmux_is_indexed (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_notify_handler ; 
 void* gmux_read32 (struct apple_gmux_data*,int /*<<< orphan*/ ) ; 
 int gmux_read8 (struct apple_gmux_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmux_read_switch_state (struct apple_gmux_data*) ; 
 int /*<<< orphan*/  gmux_write8 (struct apple_gmux_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_thunderbolt ; 
 int /*<<< orphan*/  kfree (struct apple_gmux_data*) ; 
 struct apple_gmux_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct backlight_properties*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 struct resource* pnp_get_resource (struct pnp_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnp_set_drvdata (struct pnp_dev*,struct apple_gmux_data*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_region (scalar_t__,scalar_t__,char*) ; 
 int vga_switcheroo_register_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmux_probe(struct pnp_dev *pnp, const struct pnp_device_id *id)
{
	struct apple_gmux_data *gmux_data;
	struct resource *res;
	struct backlight_properties props;
	struct backlight_device *bdev;
	u8 ver_major, ver_minor, ver_release;
	int ret = -ENXIO;
	acpi_status status;
	unsigned long long gpe;

	if (apple_gmux_data)
		return -EBUSY;

	gmux_data = kzalloc(sizeof(*gmux_data), GFP_KERNEL);
	if (!gmux_data)
		return -ENOMEM;
	pnp_set_drvdata(pnp, gmux_data);

	res = pnp_get_resource(pnp, IORESOURCE_IO, 0);
	if (!res) {
		pr_err("Failed to find gmux I/O resource\n");
		goto err_free;
	}

	gmux_data->iostart = res->start;
	gmux_data->iolen = res->end - res->start;

	if (gmux_data->iolen < GMUX_MIN_IO_LEN) {
		pr_err("gmux I/O region too small (%lu < %u)\n",
		       gmux_data->iolen, GMUX_MIN_IO_LEN);
		goto err_free;
	}

	if (!request_region(gmux_data->iostart, gmux_data->iolen,
			    "Apple gmux")) {
		pr_err("gmux I/O already in use\n");
		goto err_free;
	}

	/*
	 * Invalid version information may indicate either that the gmux
	 * device isn't present or that it's a new one that uses indexed
	 * io
	 */

	ver_major = gmux_read8(gmux_data, GMUX_PORT_VERSION_MAJOR);
	ver_minor = gmux_read8(gmux_data, GMUX_PORT_VERSION_MINOR);
	ver_release = gmux_read8(gmux_data, GMUX_PORT_VERSION_RELEASE);
	if (ver_major == 0xff && ver_minor == 0xff && ver_release == 0xff) {
		if (gmux_is_indexed(gmux_data)) {
			u32 version;
			mutex_init(&gmux_data->index_lock);
			gmux_data->indexed = true;
			version = gmux_read32(gmux_data,
				GMUX_PORT_VERSION_MAJOR);
			ver_major = (version >> 24) & 0xff;
			ver_minor = (version >> 16) & 0xff;
			ver_release = (version >> 8) & 0xff;
		} else {
			pr_info("gmux device not present\n");
			ret = -ENODEV;
			goto err_release;
		}
	}
	pr_info("Found gmux version %d.%d.%d [%s]\n", ver_major, ver_minor,
		ver_release, (gmux_data->indexed ? "indexed" : "classic"));

	memset(&props, 0, sizeof(props));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = gmux_read32(gmux_data, GMUX_PORT_MAX_BRIGHTNESS);

	/*
	 * Currently it's assumed that the maximum brightness is less than
	 * 2^24 for compatibility with old gmux versions. Cap the max
	 * brightness at this value, but print a warning if the hardware
	 * reports something higher so that it can be fixed.
	 */
	if (WARN_ON(props.max_brightness > GMUX_MAX_BRIGHTNESS))
		props.max_brightness = GMUX_MAX_BRIGHTNESS;

	bdev = backlight_device_register("gmux_backlight", &pnp->dev,
					 gmux_data, &gmux_bl_ops, &props);
	if (IS_ERR(bdev)) {
		ret = PTR_ERR(bdev);
		goto err_release;
	}

	gmux_data->bdev = bdev;
	bdev->props.brightness = gmux_get_brightness(bdev);
	backlight_update_status(bdev);

	/*
	 * The backlight situation on Macs is complicated. If the gmux is
	 * present it's the best choice, because it always works for
	 * backlight control and supports more levels than other options.
	 * Disable the other backlight choices.
	 */
	acpi_video_set_dmi_backlight_type(acpi_backlight_vendor);
	apple_bl_unregister();

	gmux_data->power_state = VGA_SWITCHEROO_ON;

	gmux_data->dhandle = ACPI_HANDLE(&pnp->dev);
	if (!gmux_data->dhandle) {
		pr_err("Cannot find acpi handle for pnp device %s\n",
		       dev_name(&pnp->dev));
		ret = -ENODEV;
		goto err_notify;
	}

	status = acpi_evaluate_integer(gmux_data->dhandle, "GMGP", NULL, &gpe);
	if (ACPI_SUCCESS(status)) {
		gmux_data->gpe = (int)gpe;

		status = acpi_install_notify_handler(gmux_data->dhandle,
						     ACPI_DEVICE_NOTIFY,
						     &gmux_notify_handler, pnp);
		if (ACPI_FAILURE(status)) {
			pr_err("Install notify handler failed: %s\n",
			       acpi_format_exception(status));
			ret = -ENODEV;
			goto err_notify;
		}

		status = acpi_enable_gpe(NULL, gmux_data->gpe);
		if (ACPI_FAILURE(status)) {
			pr_err("Cannot enable gpe: %s\n",
			       acpi_format_exception(status));
			goto err_enable_gpe;
		}
	} else {
		pr_warn("No GPE found for gmux\n");
		gmux_data->gpe = -1;
	}

	/*
	 * If Thunderbolt is present, the external DP port is not fully
	 * switchable. Force its AUX channel to the discrete GPU.
	 */
	gmux_data->external_switchable =
		!bus_for_each_dev(&pci_bus_type, NULL, NULL, is_thunderbolt);
	if (!gmux_data->external_switchable)
		gmux_write8(gmux_data, GMUX_PORT_SWITCH_EXTERNAL, 3);

	apple_gmux_data = gmux_data;
	init_completion(&gmux_data->powerchange_done);
	gmux_enable_interrupts(gmux_data);
	gmux_read_switch_state(gmux_data);

	/*
	 * Retina MacBook Pros cannot switch the panel's AUX separately
	 * and need eDP pre-calibration. They are distinguishable from
	 * pre-retinas by having an "indexed" gmux.
	 *
	 * Pre-retina MacBook Pros can switch the panel's DDC separately.
	 */
	if (gmux_data->indexed)
		ret = vga_switcheroo_register_handler(&gmux_handler_indexed,
					      VGA_SWITCHEROO_NEEDS_EDP_CONFIG);
	else
		ret = vga_switcheroo_register_handler(&gmux_handler_classic,
					      VGA_SWITCHEROO_CAN_SWITCH_DDC);
	if (ret) {
		pr_err("Failed to register vga_switcheroo handler\n");
		goto err_register_handler;
	}

	return 0;

err_register_handler:
	gmux_disable_interrupts(gmux_data);
	apple_gmux_data = NULL;
	if (gmux_data->gpe >= 0)
		acpi_disable_gpe(NULL, gmux_data->gpe);
err_enable_gpe:
	if (gmux_data->gpe >= 0)
		acpi_remove_notify_handler(gmux_data->dhandle,
					   ACPI_DEVICE_NOTIFY,
					   &gmux_notify_handler);
err_notify:
	backlight_device_unregister(bdev);
err_release:
	release_region(gmux_data->iostart, gmux_data->iolen);
err_free:
	kfree(gmux_data);
	return ret;
}