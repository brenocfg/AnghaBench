#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct usb_interface_assoc_descriptor {int bFirstInterface; } ;
struct device {int dummy; } ;
struct usb_interface {int num_altsetting; TYPE_8__* altsetting; struct device dev; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct TYPE_18__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {int speed; char* manufacturer; char* product; int /*<<< orphan*/  dev; TYPE_13__* actconfig; TYPE_12__ descriptor; TYPE_11__* config; } ;
struct TYPE_20__ {int /*<<< orphan*/  mdev; } ;
struct TYPE_26__ {int num_alt; int* alt_max_pkt_size; int /*<<< orphan*/  end_point_addr; } ;
struct TYPE_23__ {int ts1_source; TYPE_2__* hs_config_info; } ;
struct TYPE_29__ {int alt; } ;
struct cx231xx {int devno; scalar_t__ model; int has_alsa_audio; int power_mode; size_t max_iad_interface_count; TYPE_14__ v4l2_dev; int /*<<< orphan*/  media_dev; TYPE_6__ ts1_mode; TYPE_3__ current_pcb_config; int /*<<< orphan*/  interface_count; int /*<<< orphan*/  USE_ISO; scalar_t__ mode_tv; scalar_t__ vbi_or_sliced_cc_mode; int /*<<< orphan*/  devlist_count; scalar_t__ xc_fw_load_done; scalar_t__ gpio_val; scalar_t__ gpio_dir; struct device* dev; TYPE_9__ video_mode; int /*<<< orphan*/  name; } ;
struct TYPE_27__ {int bInterfaceNumber; int bNumEndpoints; } ;
struct TYPE_28__ {TYPE_5__* endpoint; TYPE_7__ desc; } ;
struct TYPE_24__ {int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_25__ {TYPE_4__ desc; } ;
struct TYPE_21__ {size_t ts1_index; } ;
struct TYPE_22__ {TYPE_1__ interface_info; } ;
struct TYPE_19__ {struct usb_interface** interface; struct usb_interface_assoc_descriptor** intf_assoc; } ;
struct TYPE_16__ {size_t bNumInterfaces; } ;
struct TYPE_17__ {TYPE_10__ desc; } ;

/* Variables and functions */
 scalar_t__ CX231XX_BOARD_CNXT_RDE_253S ; 
 scalar_t__ CX231XX_BOARD_CNXT_VIDEO_GRABBER ; 
 int CX231XX_MAXBOARDS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDEX_VIDEO ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_UNKNOWN 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx231xx_417_unregister (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_close_extension (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_dev_uninit (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_devused ; 
 int /*<<< orphan*/  cx231xx_enable_OSC (struct cx231xx*) ; 
 int cx231xx_init_dev (struct cx231xx*,struct usb_device*,int) ; 
 int cx231xx_init_v4l2 (struct cx231xx*,struct usb_device*,struct usb_interface*,int) ; 
 int /*<<< orphan*/  cx231xx_ir_exit (struct cx231xx*) ; 
 int cx231xx_media_device_init (struct cx231xx*,struct usb_device*) ; 
 int /*<<< orphan*/  cx231xx_release_analog_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_release_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_remove_from_devlist (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_reset_out (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx231xx_set_model (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_sleep_s5h1432 (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_unregister_media_device (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_v4l2_create_entities (struct cx231xx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,...) ; 
 int* devm_kmalloc_array (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct cx231xx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int media_device_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_modules (struct cx231xx*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ test_and_set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transfer_mode ; 
 struct usb_device* usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct cx231xx*) ; 
 int v4l2_device_register (struct device*,TYPE_14__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_14__*) ; 
 int v4l2_mc_create_media_graph (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx231xx_usb_probe(struct usb_interface *interface,
			     const struct usb_device_id *id)
{
	struct usb_device *udev;
	struct device *d = &interface->dev;
	struct usb_interface *uif;
	struct cx231xx *dev = NULL;
	int retval = -ENODEV;
	int nr = 0, ifnum;
	int i, isoc_pipe = 0;
	char *speed;
	u8 idx;
	struct usb_interface_assoc_descriptor *assoc_desc;

	ifnum = interface->altsetting[0].desc.bInterfaceNumber;

	/*
	 * Interface number 0 - IR interface (handled by mceusb driver)
	 * Interface number 1 - AV interface (handled by this driver)
	 */
	if (ifnum != 1)
		return -ENODEV;

	/* Check to see next free device and mark as used */
	do {
		nr = find_first_zero_bit(&cx231xx_devused, CX231XX_MAXBOARDS);
		if (nr >= CX231XX_MAXBOARDS) {
			/* No free device slots */
			dev_err(d,
				"Supports only %i devices.\n",
				CX231XX_MAXBOARDS);
			return -ENOMEM;
		}
	} while (test_and_set_bit(nr, &cx231xx_devused));

	udev = usb_get_dev(interface_to_usbdev(interface));

	/* allocate memory for our device state and initialize it */
	dev = devm_kzalloc(&udev->dev, sizeof(*dev), GFP_KERNEL);
	if (dev == NULL) {
		retval = -ENOMEM;
		goto err_if;
	}

	snprintf(dev->name, 29, "cx231xx #%d", nr);
	dev->devno = nr;
	dev->model = id->driver_info;
	dev->video_mode.alt = -1;
	dev->dev = d;

	cx231xx_set_model(dev);

	dev->interface_count++;
	/* reset gpio dir and value */
	dev->gpio_dir = 0;
	dev->gpio_val = 0;
	dev->xc_fw_load_done = 0;
	dev->has_alsa_audio = 1;
	dev->power_mode = -1;
	atomic_set(&dev->devlist_count, 0);

	/* 0 - vbi ; 1 -sliced cc mode */
	dev->vbi_or_sliced_cc_mode = 0;

	/* get maximum no.of IAD interfaces */
	dev->max_iad_interface_count = udev->config->desc.bNumInterfaces;

	/* init CIR module TBD */

	/*mode_tv: digital=1 or analog=0*/
	dev->mode_tv = 0;

	dev->USE_ISO = transfer_mode;

	switch (udev->speed) {
	case USB_SPEED_LOW:
		speed = "1.5";
		break;
	case USB_SPEED_UNKNOWN:
	case USB_SPEED_FULL:
		speed = "12";
		break;
	case USB_SPEED_HIGH:
		speed = "480";
		break;
	default:
		speed = "unknown";
	}

	dev_info(d,
		 "New device %s %s @ %s Mbps (%04x:%04x) with %d interfaces\n",
		 udev->manufacturer ? udev->manufacturer : "",
		 udev->product ? udev->product : "",
		 speed,
		 le16_to_cpu(udev->descriptor.idVendor),
		 le16_to_cpu(udev->descriptor.idProduct),
		 dev->max_iad_interface_count);

	/* increment interface count */
	dev->interface_count++;

	/* get device number */
	nr = dev->devno;

	assoc_desc = udev->actconfig->intf_assoc[0];
	if (!assoc_desc || assoc_desc->bFirstInterface != ifnum) {
		dev_err(d, "Not found matching IAD interface\n");
		retval = -ENODEV;
		goto err_if;
	}

	dev_dbg(d, "registering interface %d\n", ifnum);

	/* save our data pointer in this interface device */
	usb_set_intfdata(interface, dev);

	/* Initialize the media controller */
	retval = cx231xx_media_device_init(dev, udev);
	if (retval) {
		dev_err(d, "cx231xx_media_device_init failed\n");
		goto err_media_init;
	}

	/* Create v4l2 device */
#ifdef CONFIG_MEDIA_CONTROLLER
	dev->v4l2_dev.mdev = dev->media_dev;
#endif
	retval = v4l2_device_register(&interface->dev, &dev->v4l2_dev);
	if (retval) {
		dev_err(d, "v4l2_device_register failed\n");
		goto err_v4l2;
	}

	/* allocate device struct */
	retval = cx231xx_init_dev(dev, udev, nr);
	if (retval)
		goto err_init;

	retval = cx231xx_init_v4l2(dev, udev, interface, isoc_pipe);
	if (retval)
		goto err_init;

	if (dev->current_pcb_config.ts1_source != 0xff) {
		/* compute alternate max packet sizes for TS1 */
		idx = dev->current_pcb_config.hs_config_info[0].interface_info.ts1_index + 1;
		if (idx >= dev->max_iad_interface_count) {
			dev_err(d, "TS1 PCB interface #%d doesn't exist\n",
				idx);
			retval = -ENODEV;
			goto err_video_alt;
		}
		uif = udev->actconfig->interface[idx];

		if (uif->altsetting[0].desc.bNumEndpoints < isoc_pipe + 1) {
			retval = -ENODEV;
			goto err_video_alt;
		}

		dev->ts1_mode.end_point_addr =
		    uif->altsetting[0].endpoint[isoc_pipe].
				desc.bEndpointAddress;

		dev->ts1_mode.num_alt = uif->num_altsetting;
		dev_info(d,
			 "TS EndPoint Addr 0x%x, Alternate settings: %i\n",
			 dev->ts1_mode.end_point_addr,
			 dev->ts1_mode.num_alt);

		dev->ts1_mode.alt_max_pkt_size = devm_kmalloc_array(&udev->dev, 32, dev->ts1_mode.num_alt, GFP_KERNEL);
		if (dev->ts1_mode.alt_max_pkt_size == NULL) {
			retval = -ENOMEM;
			goto err_video_alt;
		}

		for (i = 0; i < dev->ts1_mode.num_alt; i++) {
			u16 tmp;

			if (uif->altsetting[i].desc.bNumEndpoints < isoc_pipe + 1) {
				retval = -ENODEV;
				goto err_video_alt;
			}

			tmp = le16_to_cpu(uif->altsetting[i].
						endpoint[isoc_pipe].desc.
						wMaxPacketSize);
			dev->ts1_mode.alt_max_pkt_size[i] =
			    (tmp & 0x07ff) * (((tmp & 0x1800) >> 11) + 1);
			dev_dbg(d, "Alternate setting %i, max size= %i\n",
				i, dev->ts1_mode.alt_max_pkt_size[i]);
		}
	}

	if (dev->model == CX231XX_BOARD_CNXT_VIDEO_GRABBER) {
		cx231xx_enable_OSC(dev);
		cx231xx_reset_out(dev);
		cx231xx_set_alt_setting(dev, INDEX_VIDEO, 3);
	}

	if (dev->model == CX231XX_BOARD_CNXT_RDE_253S)
		cx231xx_sleep_s5h1432(dev);

	/* load other modules required */
	request_modules(dev);

#ifdef CONFIG_MEDIA_CONTROLLER
	/* Init entities at the Media Controller */
	cx231xx_v4l2_create_entities(dev);

	retval = v4l2_mc_create_media_graph(dev->media_dev);
	if (!retval)
		retval = media_device_register(dev->media_dev);
#endif
	if (retval < 0)
		cx231xx_release_resources(dev);
	return retval;

err_video_alt:
	/* cx231xx_uninit_dev: */
	cx231xx_close_extension(dev);
	cx231xx_ir_exit(dev);
	cx231xx_release_analog_resources(dev);
	cx231xx_417_unregister(dev);
	cx231xx_remove_from_devlist(dev);
	cx231xx_dev_uninit(dev);
err_init:
	v4l2_device_unregister(&dev->v4l2_dev);
err_v4l2:
	cx231xx_unregister_media_device(dev);
err_media_init:
	usb_set_intfdata(interface, NULL);
err_if:
	usb_put_dev(udev);
	clear_bit(nr, &cx231xx_devused);
	return retval;
}