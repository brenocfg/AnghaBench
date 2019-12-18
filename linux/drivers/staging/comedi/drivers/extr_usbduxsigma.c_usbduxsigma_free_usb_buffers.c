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
struct usbduxsigma_private {int n_ao_urbs; int n_ai_urbs; struct urb** dux_commands; struct urb** in_buf; struct urb** insn_buf; struct urb** ai_urbs; struct urb** ao_urbs; struct urb* pwm_urb; } ;
struct urb {struct urb** transfer_buffer; } ;
struct comedi_device {struct usbduxsigma_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void usbduxsigma_free_usb_buffers(struct comedi_device *dev)
{
	struct usbduxsigma_private *devpriv = dev->private;
	struct urb *urb;
	int i;

	urb = devpriv->pwm_urb;
	if (urb) {
		kfree(urb->transfer_buffer);
		usb_free_urb(urb);
	}
	if (devpriv->ao_urbs) {
		for (i = 0; i < devpriv->n_ao_urbs; i++) {
			urb = devpriv->ao_urbs[i];
			if (urb) {
				kfree(urb->transfer_buffer);
				usb_free_urb(urb);
			}
		}
		kfree(devpriv->ao_urbs);
	}
	if (devpriv->ai_urbs) {
		for (i = 0; i < devpriv->n_ai_urbs; i++) {
			urb = devpriv->ai_urbs[i];
			if (urb) {
				kfree(urb->transfer_buffer);
				usb_free_urb(urb);
			}
		}
		kfree(devpriv->ai_urbs);
	}
	kfree(devpriv->insn_buf);
	kfree(devpriv->in_buf);
	kfree(devpriv->dux_commands);
}