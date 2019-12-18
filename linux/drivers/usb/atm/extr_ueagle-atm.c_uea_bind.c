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
struct usbatm_data {int flags; struct uea_softc* driver_data; } ;
struct usb_interface {TYPE_2__* altsetting; } ;
struct usb_device_id {int driver_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  bcdDevice; } ;
struct usb_device {TYPE_3__ descriptor; } ;
struct uea_softc {size_t modem_index; int driver_info; struct usb_device* usb_dev; void* annex; struct usbatm_data* usbatm; } ;
struct TYPE_4__ {int bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 scalar_t__ ADI930 ; 
 void* ANNEXA ; 
 void* ANNEXB ; 
 int AUTO_ANNEX_A ; 
 int AUTO_ANNEX_B ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NB_MODEM ; 
 int UDSL_IGNORE_EILSEQ ; 
 int UDSL_SKIP_HEAVY_INIT ; 
 int UDSL_USE_ISOC ; 
 scalar_t__ UEA_CHIP_VERSION (struct usb_device_id const*) ; 
 int /*<<< orphan*/  UEA_DS_IFACE_NO ; 
 int UEA_INTR_IFACE_NO ; 
 int /*<<< orphan*/  UEA_US_IFACE_NO ; 
 unsigned int* altsetting ; 
 int* annex ; 
 int claim_interface (struct usb_device*,struct usbatm_data*,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct uea_softc*) ; 
 struct uea_softc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 size_t modem_index ; 
 scalar_t__* sync_wait ; 
 int uea_boot (struct uea_softc*) ; 
 int /*<<< orphan*/  uea_dbg (struct usb_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  uea_enters (struct usb_device*) ; 
 int /*<<< orphan*/  uea_err (struct usb_device*,char*,unsigned int) ; 
 int /*<<< orphan*/  uea_info (struct usb_device*,char*) ; 
 scalar_t__ usb_set_interface (struct usb_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int uea_bind(struct usbatm_data *usbatm, struct usb_interface *intf,
		   const struct usb_device_id *id)
{
	struct usb_device *usb = interface_to_usbdev(intf);
	struct uea_softc *sc;
	int ret, ifnum = intf->altsetting->desc.bInterfaceNumber;
	unsigned int alt;

	uea_enters(usb);

	/* interface 0 is for firmware/monitoring */
	if (ifnum != UEA_INTR_IFACE_NO)
		return -ENODEV;

	usbatm->flags = (sync_wait[modem_index] ? 0 : UDSL_SKIP_HEAVY_INIT);

	/* interface 1 is for outbound traffic */
	ret = claim_interface(usb, usbatm, UEA_US_IFACE_NO);
	if (ret < 0)
		return ret;

	/* ADI930 has only 2 interfaces and inbound traffic is on interface 1 */
	if (UEA_CHIP_VERSION(id) != ADI930) {
		/* interface 2 is for inbound traffic */
		ret = claim_interface(usb, usbatm, UEA_DS_IFACE_NO);
		if (ret < 0)
			return ret;
	}

	sc = kzalloc(sizeof(struct uea_softc), GFP_KERNEL);
	if (!sc)
		return -ENOMEM;

	sc->usb_dev = usb;
	usbatm->driver_data = sc;
	sc->usbatm = usbatm;
	sc->modem_index = (modem_index < NB_MODEM) ? modem_index++ : 0;
	sc->driver_info = id->driver_info;

	/* first try to use module parameter */
	if (annex[sc->modem_index] == 1)
		sc->annex = ANNEXA;
	else if (annex[sc->modem_index] == 2)
		sc->annex = ANNEXB;
	/* try to autodetect annex */
	else if (sc->driver_info & AUTO_ANNEX_A)
		sc->annex = ANNEXA;
	else if (sc->driver_info & AUTO_ANNEX_B)
		sc->annex = ANNEXB;
	else
		sc->annex = (le16_to_cpu
		(sc->usb_dev->descriptor.bcdDevice) & 0x80) ? ANNEXB : ANNEXA;

	alt = altsetting[sc->modem_index];
	/* ADI930 don't support iso */
	if (UEA_CHIP_VERSION(id) != ADI930 && alt > 0) {
		if (alt <= 8 &&
			usb_set_interface(usb, UEA_DS_IFACE_NO, alt) == 0) {
			uea_dbg(usb, "set alternate %u for 2 interface\n", alt);
			uea_info(usb, "using iso mode\n");
			usbatm->flags |= UDSL_USE_ISOC | UDSL_IGNORE_EILSEQ;
		} else {
			uea_err(usb, "setting alternate %u failed for "
					"2 interface, using bulk mode\n", alt);
		}
	}

	ret = uea_boot(sc);
	if (ret < 0)
		goto error;

	return 0;

error:
	kfree(sc);
	return ret;
}