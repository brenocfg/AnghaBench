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
struct device {int dummy; } ;
struct brcmf_usbdev_info {struct device* dev; int /*<<< orphan*/  dev_init_done; int /*<<< orphan*/  settings; } ;
struct brcmf_usbdev {int /*<<< orphan*/  chiprev; int /*<<< orphan*/  devid; struct brcmf_fw_request* bus; } ;
struct TYPE_2__ {struct brcmf_usbdev* usb; } ;
struct brcmf_fw_request {int always_use_fws_queue; int wowl_supported; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; struct device* dev; int /*<<< orphan*/  proto_type; int /*<<< orphan*/ * ops; TYPE_1__ bus_priv; } ;
struct brcmf_bus {int always_use_fws_queue; int wowl_supported; int /*<<< orphan*/  chiprev; int /*<<< orphan*/  chip; struct device* dev; int /*<<< orphan*/  proto_type; int /*<<< orphan*/ * ops; TYPE_1__ bus_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BUSTYPE_USB ; 
 int /*<<< orphan*/  BRCMF_PROTO_BCDC ; 
 int /*<<< orphan*/  BRCMF_USB_NRXQ ; 
 int /*<<< orphan*/  BRCMF_USB_NTXQ ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  USB ; 
 int brcmf_alloc (struct device*,int /*<<< orphan*/ ) ; 
 int brcmf_attach (struct device*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_free (struct device*) ; 
 int brcmf_fw_get_firmwares (struct device*,struct brcmf_fw_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_get_module_param (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct brcmf_usbdev* brcmf_usb_attach (struct brcmf_usbdev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_usb_bus_ops ; 
 int /*<<< orphan*/  brcmf_usb_detach (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_usb_dlneeded (struct brcmf_usbdev_info*) ; 
 struct brcmf_fw_request* brcmf_usb_prepare_fw_request (struct brcmf_usbdev_info*) ; 
 int /*<<< orphan*/  brcmf_usb_probe_phase2 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct brcmf_fw_request*) ; 
 int /*<<< orphan*/  kfree (struct brcmf_fw_request*) ; 
 struct brcmf_fw_request* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_usb_probe_cb(struct brcmf_usbdev_info *devinfo)
{
	struct brcmf_bus *bus = NULL;
	struct brcmf_usbdev *bus_pub = NULL;
	struct device *dev = devinfo->dev;
	struct brcmf_fw_request *fwreq;
	int ret;

	brcmf_dbg(USB, "Enter\n");
	bus_pub = brcmf_usb_attach(devinfo, BRCMF_USB_NRXQ, BRCMF_USB_NTXQ);
	if (!bus_pub)
		return -ENODEV;

	bus = kzalloc(sizeof(struct brcmf_bus), GFP_ATOMIC);
	if (!bus) {
		ret = -ENOMEM;
		goto fail;
	}

	bus->dev = dev;
	bus_pub->bus = bus;
	bus->bus_priv.usb = bus_pub;
	dev_set_drvdata(dev, bus);
	bus->ops = &brcmf_usb_bus_ops;
	bus->proto_type = BRCMF_PROTO_BCDC;
	bus->always_use_fws_queue = true;
#ifdef CONFIG_PM
	bus->wowl_supported = true;
#endif

	devinfo->settings = brcmf_get_module_param(bus->dev, BRCMF_BUSTYPE_USB,
						   bus_pub->devid,
						   bus_pub->chiprev);
	if (!devinfo->settings) {
		ret = -ENOMEM;
		goto fail;
	}

	if (!brcmf_usb_dlneeded(devinfo)) {
		ret = brcmf_alloc(devinfo->dev, devinfo->settings);
		if (ret)
			goto fail;
		ret = brcmf_attach(devinfo->dev);
		if (ret)
			goto fail;
		/* we are done */
		complete(&devinfo->dev_init_done);
		return 0;
	}
	bus->chip = bus_pub->devid;
	bus->chiprev = bus_pub->chiprev;

	fwreq = brcmf_usb_prepare_fw_request(devinfo);
	if (!fwreq) {
		ret = -ENOMEM;
		goto fail;
	}

	/* request firmware here */
	ret = brcmf_fw_get_firmwares(dev, fwreq, brcmf_usb_probe_phase2);
	if (ret) {
		brcmf_err("firmware request failed: %d\n", ret);
		kfree(fwreq);
		goto fail;
	}

	return 0;

fail:
	/* Release resources in reverse order */
	brcmf_free(devinfo->dev);
	kfree(bus);
	brcmf_usb_detach(devinfo);
	return ret;
}