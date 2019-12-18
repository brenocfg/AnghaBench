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
struct usb_interface {int /*<<< orphan*/  dev; TYPE_3__* cur_altsetting; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct ar9170 {int usb_ep_cmd_is_bulk; struct usb_device* udev; int /*<<< orphan*/  rx_pool_urbs; int /*<<< orphan*/  rx_anch_urbs; int /*<<< orphan*/  rx_work_urbs; int /*<<< orphan*/  tx_anch_urbs; int /*<<< orphan*/  tx_cmd_urbs; int /*<<< orphan*/  usb_tasklet; int /*<<< orphan*/  fw_load_wait; int /*<<< orphan*/  fw_boot_wait; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  tx_err; int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  tx_anch; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  rx_pool; int /*<<< orphan*/  rx_anch; int /*<<< orphan*/  hw; int /*<<< orphan*/  features; struct usb_interface* intf; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct TYPE_6__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 scalar_t__ AR9170_USB_EP_CMD ; 
 int /*<<< orphan*/  CARL9170FW_NAME ; 
 int /*<<< orphan*/  CARL9170_STOPPED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ar9170*) ; 
 int PTR_ERR (struct ar9170*) ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ USB_ENDPOINT_XFER_BULK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ar9170* carl9170_alloc (int) ; 
 int /*<<< orphan*/  carl9170_free (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_set_state (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_usb_firmware_step2 ; 
 int /*<<< orphan*/  carl9170_usb_tasklet ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_num (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_type (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_get_intf (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_intf (struct usb_interface*) ; 
 int usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ar9170*) ; 

__attribute__((used)) static int carl9170_usb_probe(struct usb_interface *intf,
			      const struct usb_device_id *id)
{
	struct usb_endpoint_descriptor *ep;
	struct ar9170 *ar;
	struct usb_device *udev;
	int i, err;

	err = usb_reset_device(interface_to_usbdev(intf));
	if (err)
		return err;

	ar = carl9170_alloc(sizeof(*ar));
	if (IS_ERR(ar))
		return PTR_ERR(ar);

	udev = interface_to_usbdev(intf);
	ar->udev = udev;
	ar->intf = intf;
	ar->features = id->driver_info;

	/* We need to remember the type of endpoint 4 because it differs
	 * between high- and full-speed configuration. The high-speed
	 * configuration specifies it as interrupt and the full-speed
	 * configuration as bulk endpoint. This information is required
	 * later when sending urbs to that endpoint.
	 */
	for (i = 0; i < intf->cur_altsetting->desc.bNumEndpoints; ++i) {
		ep = &intf->cur_altsetting->endpoint[i].desc;

		if (usb_endpoint_num(ep) == AR9170_USB_EP_CMD &&
		    usb_endpoint_dir_out(ep) &&
		    usb_endpoint_type(ep) == USB_ENDPOINT_XFER_BULK)
			ar->usb_ep_cmd_is_bulk = true;
	}

	usb_set_intfdata(intf, ar);
	SET_IEEE80211_DEV(ar->hw, &intf->dev);

	init_usb_anchor(&ar->rx_anch);
	init_usb_anchor(&ar->rx_pool);
	init_usb_anchor(&ar->rx_work);
	init_usb_anchor(&ar->tx_wait);
	init_usb_anchor(&ar->tx_anch);
	init_usb_anchor(&ar->tx_cmd);
	init_usb_anchor(&ar->tx_err);
	init_completion(&ar->cmd_wait);
	init_completion(&ar->fw_boot_wait);
	init_completion(&ar->fw_load_wait);
	tasklet_init(&ar->usb_tasklet, carl9170_usb_tasklet,
		     (unsigned long)ar);

	atomic_set(&ar->tx_cmd_urbs, 0);
	atomic_set(&ar->tx_anch_urbs, 0);
	atomic_set(&ar->rx_work_urbs, 0);
	atomic_set(&ar->rx_anch_urbs, 0);
	atomic_set(&ar->rx_pool_urbs, 0);

	usb_get_intf(intf);

	carl9170_set_state(ar, CARL9170_STOPPED);

	err = request_firmware_nowait(THIS_MODULE, 1, CARL9170FW_NAME,
		&ar->udev->dev, GFP_KERNEL, ar, carl9170_usb_firmware_step2);
	if (err) {
		usb_put_intf(intf);
		carl9170_free(ar);
	}
	return err;
}