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
struct usbtest_param_32 {int sglen; int iterations; int /*<<< orphan*/  length; } ;
struct usbtest_dev {TYPE_1__* intf; } ;
struct usb_endpoint_descriptor {int bInterval; } ;
struct usb_device {scalar_t__ speed; } ;
struct urb {struct transfer_context* context; scalar_t__ number_of_packets; } ;
struct transfer_context {int count; int is_iso; int submit_error; int errors; int packet_count; int /*<<< orphan*/  done; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending; struct usbtest_dev* dev; } ;
typedef  int /*<<< orphan*/  context ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_SGLEN ; 
 int UINT_MAX ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 struct urb* complicated_alloc_urb (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned long,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct urb* iso_alloc_urb (struct usb_device*,int,struct usb_endpoint_descriptor*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct transfer_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_free_urb (struct urb*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int ss_isoc_get_packet_num (struct usb_device*,int) ; 
 struct usb_device* testdev_to_usbdev (struct usbtest_dev*) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int usb_endpoint_maxp_mult (struct usb_endpoint_descriptor*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
test_queue(struct usbtest_dev *dev, struct usbtest_param_32 *param,
		int pipe, struct usb_endpoint_descriptor *desc, unsigned offset)
{
	struct transfer_context	context;
	struct usb_device	*udev;
	unsigned		i;
	unsigned long		packets = 0;
	int			status = 0;
	struct urb		*urbs[MAX_SGLEN];

	if (!param->sglen || param->iterations > UINT_MAX / param->sglen)
		return -EINVAL;

	if (param->sglen > MAX_SGLEN)
		return -EINVAL;

	memset(&context, 0, sizeof(context));
	context.count = param->iterations * param->sglen;
	context.dev = dev;
	context.is_iso = !!desc;
	init_completion(&context.done);
	spin_lock_init(&context.lock);

	udev = testdev_to_usbdev(dev);

	for (i = 0; i < param->sglen; i++) {
		if (context.is_iso)
			urbs[i] = iso_alloc_urb(udev, pipe, desc,
					param->length, offset);
		else
			urbs[i] = complicated_alloc_urb(udev, pipe,
					param->length, 0);

		if (!urbs[i]) {
			status = -ENOMEM;
			goto fail;
		}
		packets += urbs[i]->number_of_packets;
		urbs[i]->context = &context;
	}
	packets *= param->iterations;

	if (context.is_iso) {
		int transaction_num;

		if (udev->speed >= USB_SPEED_SUPER)
			transaction_num = ss_isoc_get_packet_num(udev, pipe);
		else
			transaction_num = usb_endpoint_maxp_mult(desc);

		dev_info(&dev->intf->dev,
			"iso period %d %sframes, wMaxPacket %d, transactions: %d\n",
			1 << (desc->bInterval - 1),
			(udev->speed >= USB_SPEED_HIGH) ? "micro" : "",
			usb_endpoint_maxp(desc),
			transaction_num);

		dev_info(&dev->intf->dev,
			"total %lu msec (%lu packets)\n",
			(packets * (1 << (desc->bInterval - 1)))
				/ ((udev->speed >= USB_SPEED_HIGH) ? 8 : 1),
			packets);
	}

	spin_lock_irq(&context.lock);
	for (i = 0; i < param->sglen; i++) {
		++context.pending;
		status = usb_submit_urb(urbs[i], GFP_ATOMIC);
		if (status < 0) {
			ERROR(dev, "submit iso[%d], error %d\n", i, status);
			if (i == 0) {
				spin_unlock_irq(&context.lock);
				goto fail;
			}

			simple_free_urb(urbs[i]);
			urbs[i] = NULL;
			context.pending--;
			context.submit_error = 1;
			break;
		}
	}
	spin_unlock_irq(&context.lock);

	wait_for_completion(&context.done);

	for (i = 0; i < param->sglen; i++) {
		if (urbs[i])
			simple_free_urb(urbs[i]);
	}
	/*
	 * Isochronous transfers are expected to fail sometimes.  As an
	 * arbitrary limit, we will report an error if any submissions
	 * fail or if the transfer failure rate is > 10%.
	 */
	if (status != 0)
		;
	else if (context.submit_error)
		status = -EACCES;
	else if (context.errors >
			(context.is_iso ? context.packet_count / 10 : 0))
		status = -EIO;
	return status;

fail:
	for (i = 0; i < param->sglen; i++) {
		if (urbs[i])
			simple_free_urb(urbs[i]);
	}
	return status;
}