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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct ath10k_usb_pipe {int /*<<< orphan*/  io_comp_queue; int /*<<< orphan*/  io_complete_work; } ;
struct ath10k_usb {void* diag_resp_buffer; void* diag_cmd_buffer; struct ath10k_usb_pipe* pipes; struct usb_interface* interface; struct usb_device* udev; int /*<<< orphan*/  cs_lock; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_USB_MAX_DIAG_CMD ; 
 int /*<<< orphan*/  ATH10K_USB_MAX_DIAG_RESP ; 
 int ATH10K_USB_PIPE_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_usb_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_usb_io_comp_work ; 
 struct ath10k_usb* ath10k_usb_priv (struct ath10k*) ; 
 int ath10k_usb_setup_pipe_resources (struct ath10k*,struct usb_interface*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ath10k_usb*) ; 

__attribute__((used)) static int ath10k_usb_create(struct ath10k *ar,
			     struct usb_interface *interface)
{
	struct ath10k_usb *ar_usb = ath10k_usb_priv(ar);
	struct usb_device *dev = interface_to_usbdev(interface);
	struct ath10k_usb_pipe *pipe;
	int ret, i;

	usb_set_intfdata(interface, ar_usb);
	spin_lock_init(&ar_usb->cs_lock);
	ar_usb->udev = dev;
	ar_usb->interface = interface;

	for (i = 0; i < ATH10K_USB_PIPE_MAX; i++) {
		pipe = &ar_usb->pipes[i];
		INIT_WORK(&pipe->io_complete_work,
			  ath10k_usb_io_comp_work);
		skb_queue_head_init(&pipe->io_comp_queue);
	}

	ar_usb->diag_cmd_buffer = kzalloc(ATH10K_USB_MAX_DIAG_CMD, GFP_KERNEL);
	if (!ar_usb->diag_cmd_buffer) {
		ret = -ENOMEM;
		goto err;
	}

	ar_usb->diag_resp_buffer = kzalloc(ATH10K_USB_MAX_DIAG_RESP,
					   GFP_KERNEL);
	if (!ar_usb->diag_resp_buffer) {
		ret = -ENOMEM;
		goto err;
	}

	ret = ath10k_usb_setup_pipe_resources(ar, interface);
	if (ret)
		goto err;

	return 0;

err:
	ath10k_usb_destroy(ar);
	return ret;
}