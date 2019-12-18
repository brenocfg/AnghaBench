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
typedef  int u8 ;
struct usb_interface_descriptor {int bInterfaceNumber; int /*<<< orphan*/  bLength; } ;
struct usb_interface_cache {int num_altsetting; TYPE_2__* altsetting; int /*<<< orphan*/  ref; } ;
struct usb_interface_assoc_descriptor {int /*<<< orphan*/  bLength; } ;
struct TYPE_6__ {int bNumInterfaces; int bLength; int bConfigurationValue; int /*<<< orphan*/  wTotalLength; int /*<<< orphan*/  bDescriptorType; } ;
struct usb_host_config {unsigned char* extra; int extralen; struct usb_interface_cache** intf_cache; TYPE_3__ desc; struct usb_interface_assoc_descriptor** intf_assoc; } ;
struct device {int dummy; } ;
struct usb_device {int quirks; struct device dev; } ;
struct usb_descriptor_header {int bLength; int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_4__ {int bAlternateSetting; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_DT_CONFIG ; 
 int USB_DT_CONFIG_SIZE ; 
 int /*<<< orphan*/  USB_DT_DEVICE ; 
 int /*<<< orphan*/  USB_DT_INTERFACE ; 
 int /*<<< orphan*/  USB_DT_INTERFACE_ASSOCIATION ; 
 int /*<<< orphan*/  USB_DT_INTERFACE_ASSOCIATION_SIZE ; 
 int /*<<< orphan*/  USB_DT_INTERFACE_SIZE ; 
 int USB_MAXALTSETTING ; 
 unsigned int USB_MAXIADS ; 
 int USB_MAXINTERFACES ; 
 int USB_QUIRK_HONOR_BNUMINTERFACES ; 
 int /*<<< orphan*/  altsetting ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 
 int find_next_descriptor (unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct usb_interface_cache* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,unsigned char*,int) ; 
 int plural (int) ; 
 int /*<<< orphan*/  struct_size (struct usb_interface_cache*,int /*<<< orphan*/ ,int) ; 
 int usb_parse_interface (struct device*,int,struct usb_host_config*,unsigned char*,int,int*,int*) ; 

__attribute__((used)) static int usb_parse_configuration(struct usb_device *dev, int cfgidx,
    struct usb_host_config *config, unsigned char *buffer, int size)
{
	struct device *ddev = &dev->dev;
	unsigned char *buffer0 = buffer;
	int cfgno;
	int nintf, nintf_orig;
	int i, j, n;
	struct usb_interface_cache *intfc;
	unsigned char *buffer2;
	int size2;
	struct usb_descriptor_header *header;
	int retval;
	u8 inums[USB_MAXINTERFACES], nalts[USB_MAXINTERFACES];
	unsigned iad_num = 0;

	memcpy(&config->desc, buffer, USB_DT_CONFIG_SIZE);
	nintf = nintf_orig = config->desc.bNumInterfaces;
	config->desc.bNumInterfaces = 0;	// Adjusted later

	if (config->desc.bDescriptorType != USB_DT_CONFIG ||
	    config->desc.bLength < USB_DT_CONFIG_SIZE ||
	    config->desc.bLength > size) {
		dev_err(ddev, "invalid descriptor for config index %d: "
		    "type = 0x%X, length = %d\n", cfgidx,
		    config->desc.bDescriptorType, config->desc.bLength);
		return -EINVAL;
	}
	cfgno = config->desc.bConfigurationValue;

	buffer += config->desc.bLength;
	size -= config->desc.bLength;

	if (nintf > USB_MAXINTERFACES) {
		dev_warn(ddev, "config %d has too many interfaces: %d, "
		    "using maximum allowed: %d\n",
		    cfgno, nintf, USB_MAXINTERFACES);
		nintf = USB_MAXINTERFACES;
	}

	/* Go through the descriptors, checking their length and counting the
	 * number of altsettings for each interface */
	n = 0;
	for ((buffer2 = buffer, size2 = size);
	      size2 > 0;
	     (buffer2 += header->bLength, size2 -= header->bLength)) {

		if (size2 < sizeof(struct usb_descriptor_header)) {
			dev_warn(ddev, "config %d descriptor has %d excess "
			    "byte%s, ignoring\n",
			    cfgno, size2, plural(size2));
			break;
		}

		header = (struct usb_descriptor_header *) buffer2;
		if ((header->bLength > size2) || (header->bLength < 2)) {
			dev_warn(ddev, "config %d has an invalid descriptor "
			    "of length %d, skipping remainder of the config\n",
			    cfgno, header->bLength);
			break;
		}

		if (header->bDescriptorType == USB_DT_INTERFACE) {
			struct usb_interface_descriptor *d;
			int inum;

			d = (struct usb_interface_descriptor *) header;
			if (d->bLength < USB_DT_INTERFACE_SIZE) {
				dev_warn(ddev, "config %d has an invalid "
				    "interface descriptor of length %d, "
				    "skipping\n", cfgno, d->bLength);
				continue;
			}

			inum = d->bInterfaceNumber;

			if ((dev->quirks & USB_QUIRK_HONOR_BNUMINTERFACES) &&
			    n >= nintf_orig) {
				dev_warn(ddev, "config %d has more interface "
				    "descriptors, than it declares in "
				    "bNumInterfaces, ignoring interface "
				    "number: %d\n", cfgno, inum);
				continue;
			}

			if (inum >= nintf_orig)
				dev_warn(ddev, "config %d has an invalid "
				    "interface number: %d but max is %d\n",
				    cfgno, inum, nintf_orig - 1);

			/* Have we already encountered this interface?
			 * Count its altsettings */
			for (i = 0; i < n; ++i) {
				if (inums[i] == inum)
					break;
			}
			if (i < n) {
				if (nalts[i] < 255)
					++nalts[i];
			} else if (n < USB_MAXINTERFACES) {
				inums[n] = inum;
				nalts[n] = 1;
				++n;
			}

		} else if (header->bDescriptorType ==
				USB_DT_INTERFACE_ASSOCIATION) {
			struct usb_interface_assoc_descriptor *d;

			d = (struct usb_interface_assoc_descriptor *)header;
			if (d->bLength < USB_DT_INTERFACE_ASSOCIATION_SIZE) {
				dev_warn(ddev,
					 "config %d has an invalid interface association descriptor of length %d, skipping\n",
					 cfgno, d->bLength);
				continue;
			}

			if (iad_num == USB_MAXIADS) {
				dev_warn(ddev, "found more Interface "
					       "Association Descriptors "
					       "than allocated for in "
					       "configuration %d\n", cfgno);
			} else {
				config->intf_assoc[iad_num] = d;
				iad_num++;
			}

		} else if (header->bDescriptorType == USB_DT_DEVICE ||
			    header->bDescriptorType == USB_DT_CONFIG)
			dev_warn(ddev, "config %d contains an unexpected "
			    "descriptor of type 0x%X, skipping\n",
			    cfgno, header->bDescriptorType);

	}	/* for ((buffer2 = buffer, size2 = size); ...) */
	size = buffer2 - buffer;
	config->desc.wTotalLength = cpu_to_le16(buffer2 - buffer0);

	if (n != nintf)
		dev_warn(ddev, "config %d has %d interface%s, different from "
		    "the descriptor's value: %d\n",
		    cfgno, n, plural(n), nintf_orig);
	else if (n == 0)
		dev_warn(ddev, "config %d has no interfaces?\n", cfgno);
	config->desc.bNumInterfaces = nintf = n;

	/* Check for missing interface numbers */
	for (i = 0; i < nintf; ++i) {
		for (j = 0; j < nintf; ++j) {
			if (inums[j] == i)
				break;
		}
		if (j >= nintf)
			dev_warn(ddev, "config %d has no interface number "
			    "%d\n", cfgno, i);
	}

	/* Allocate the usb_interface_caches and altsetting arrays */
	for (i = 0; i < nintf; ++i) {
		j = nalts[i];
		if (j > USB_MAXALTSETTING) {
			dev_warn(ddev, "too many alternate settings for "
			    "config %d interface %d: %d, "
			    "using maximum allowed: %d\n",
			    cfgno, inums[i], j, USB_MAXALTSETTING);
			nalts[i] = j = USB_MAXALTSETTING;
		}

		intfc = kzalloc(struct_size(intfc, altsetting, j), GFP_KERNEL);
		config->intf_cache[i] = intfc;
		if (!intfc)
			return -ENOMEM;
		kref_init(&intfc->ref);
	}

	/* FIXME: parse the BOS descriptor */

	/* Skip over any Class Specific or Vendor Specific descriptors;
	 * find the first interface descriptor */
	config->extra = buffer;
	i = find_next_descriptor(buffer, size, USB_DT_INTERFACE,
	    USB_DT_INTERFACE, &n);
	config->extralen = i;
	if (n > 0)
		dev_dbg(ddev, "skipped %d descriptor%s after %s\n",
		    n, plural(n), "configuration");
	buffer += i;
	size -= i;

	/* Parse all the interface/altsetting descriptors */
	while (size > 0) {
		retval = usb_parse_interface(ddev, cfgno, config,
		    buffer, size, inums, nalts);
		if (retval < 0)
			return retval;

		buffer += retval;
		size -= retval;
	}

	/* Check for missing altsettings */
	for (i = 0; i < nintf; ++i) {
		intfc = config->intf_cache[i];
		for (j = 0; j < intfc->num_altsetting; ++j) {
			for (n = 0; n < intfc->num_altsetting; ++n) {
				if (intfc->altsetting[n].desc.
				    bAlternateSetting == j)
					break;
			}
			if (n >= intfc->num_altsetting)
				dev_warn(ddev, "config %d interface %d has no "
				    "altsetting %d\n", cfgno, inums[i], j);
		}
	}

	return 0;
}