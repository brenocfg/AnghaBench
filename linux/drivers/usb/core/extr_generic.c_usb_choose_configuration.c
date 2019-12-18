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
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; } ;
struct TYPE_8__ {scalar_t__ bNumInterfaces; int bmAttributes; int bConfigurationValue; } ;
struct usb_host_config {TYPE_4__ desc; TYPE_2__** intf_cache; } ;
struct TYPE_7__ {int bNumConfigurations; scalar_t__ bDeviceClass; } ;
struct usb_device {scalar_t__ bus_mA; int /*<<< orphan*/  dev; TYPE_3__ descriptor; struct usb_host_config* config; } ;
struct TYPE_6__ {TYPE_1__* altsetting; } ;
struct TYPE_5__ {struct usb_interface_descriptor desc; } ;

/* Variables and functions */
 scalar_t__ USB_CLASS_VENDOR_SPEC ; 
 int USB_CONFIG_ATT_SELFPOWER ; 
 scalar_t__ bus_powered ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_activesync (struct usb_interface_descriptor*) ; 
 scalar_t__ is_audio (struct usb_interface_descriptor*) ; 
 scalar_t__ is_rndis (struct usb_interface_descriptor*) ; 
 scalar_t__ is_uac3_config (struct usb_interface_descriptor*) ; 
 int /*<<< orphan*/  plural (int) ; 
 scalar_t__ usb_device_is_owned (struct usb_device*) ; 
 scalar_t__ usb_get_max_power (struct usb_device*,struct usb_host_config*) ; 

int usb_choose_configuration(struct usb_device *udev)
{
	int i;
	int num_configs;
	int insufficient_power = 0;
	struct usb_host_config *c, *best;

	if (usb_device_is_owned(udev))
		return 0;

	best = NULL;
	c = udev->config;
	num_configs = udev->descriptor.bNumConfigurations;
	for (i = 0; i < num_configs; (i++, c++)) {
		struct usb_interface_descriptor	*desc = NULL;

		/* It's possible that a config has no interfaces! */
		if (c->desc.bNumInterfaces > 0)
			desc = &c->intf_cache[0]->altsetting->desc;

		/*
		 * HP's USB bus-powered keyboard has only one configuration
		 * and it claims to be self-powered; other devices may have
		 * similar errors in their descriptors.  If the next test
		 * were allowed to execute, such configurations would always
		 * be rejected and the devices would not work as expected.
		 * In the meantime, we run the risk of selecting a config
		 * that requires external power at a time when that power
		 * isn't available.  It seems to be the lesser of two evils.
		 *
		 * Bugzilla #6448 reports a device that appears to crash
		 * when it receives a GET_DEVICE_STATUS request!  We don't
		 * have any other way to tell whether a device is self-powered,
		 * but since we don't use that information anywhere but here,
		 * the call has been removed.
		 *
		 * Maybe the GET_DEVICE_STATUS call and the test below can
		 * be reinstated when device firmwares become more reliable.
		 * Don't hold your breath.
		 */
#if 0
		/* Rule out self-powered configs for a bus-powered device */
		if (bus_powered && (c->desc.bmAttributes &
					USB_CONFIG_ATT_SELFPOWER))
			continue;
#endif

		/*
		 * The next test may not be as effective as it should be.
		 * Some hubs have errors in their descriptor, claiming
		 * to be self-powered when they are really bus-powered.
		 * We will overestimate the amount of current such hubs
		 * make available for each port.
		 *
		 * This is a fairly benign sort of failure.  It won't
		 * cause us to reject configurations that we should have
		 * accepted.
		 */

		/* Rule out configs that draw too much bus current */
		if (usb_get_max_power(udev, c) > udev->bus_mA) {
			insufficient_power++;
			continue;
		}

		/*
		 * Select first configuration as default for audio so that
		 * devices that don't comply with UAC3 protocol are supported.
		 * But, still iterate through other configurations and
		 * select UAC3 compliant config if present.
		 */
		if (desc && is_audio(desc)) {
			/* Always prefer the first found UAC3 config */
			if (is_uac3_config(desc)) {
				best = c;
				break;
			}

			/* If there is no UAC3 config, prefer the first config */
			else if (i == 0)
				best = c;

			/* Unconditional continue, because the rest of the code
			 * in the loop is irrelevant for audio devices, and
			 * because it can reassign best, which for audio devices
			 * we don't want.
			 */
			continue;
		}

		/* When the first config's first interface is one of Microsoft's
		 * pet nonstandard Ethernet-over-USB protocols, ignore it unless
		 * this kernel has enabled the necessary host side driver.
		 * But: Don't ignore it if it's the only config.
		 */
		if (i == 0 && num_configs > 1 && desc &&
				(is_rndis(desc) || is_activesync(desc))) {
#if !defined(CONFIG_USB_NET_RNDIS_HOST) && !defined(CONFIG_USB_NET_RNDIS_HOST_MODULE)
			continue;
#else
			best = c;
#endif
		}

		/* From the remaining configs, choose the first one whose
		 * first interface is for a non-vendor-specific class.
		 * Reason: Linux is more likely to have a class driver
		 * than a vendor-specific driver. */
		else if (udev->descriptor.bDeviceClass !=
						USB_CLASS_VENDOR_SPEC &&
				(desc && desc->bInterfaceClass !=
						USB_CLASS_VENDOR_SPEC)) {
			best = c;
			break;
		}

		/* If all the remaining configs are vendor-specific,
		 * choose the first one. */
		else if (!best)
			best = c;
	}

	if (insufficient_power > 0)
		dev_info(&udev->dev, "rejected %d configuration%s "
			"due to insufficient available bus power\n",
			insufficient_power, plural(insufficient_power));

	if (best) {
		i = best->desc.bConfigurationValue;
		dev_dbg(&udev->dev,
			"configuration #%d chosen from %d choice%s\n",
			i, num_configs, plural(num_configs));
	} else {
		i = -1;
		dev_warn(&udev->dev,
			"no configuration chosen from %d choice%s\n",
			num_configs, plural(num_configs));
	}
	return i;
}