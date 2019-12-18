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
struct wahc {int /*<<< orphan*/ * dti_buf; int /*<<< orphan*/  dti_buf_size; int /*<<< orphan*/ * dti_epd; int /*<<< orphan*/ * dto_epd; int /*<<< orphan*/  quirks; } ;
struct device {int dummy; } ;
struct usb_interface {TYPE_3__* cur_altsetting; struct device dev; } ;
typedef  int /*<<< orphan*/  kernel_ulong_t ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct TYPE_6__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (int /*<<< orphan*/ *) ; 
 int wa_nep_create (struct wahc*,struct usb_interface*) ; 
 int wa_rpipes_create (struct wahc*) ; 
 int /*<<< orphan*/  wa_rpipes_destroy (struct wahc*) ; 

int wa_create(struct wahc *wa, struct usb_interface *iface,
	kernel_ulong_t quirks)
{
	int result;
	struct device *dev = &iface->dev;

	if (iface->cur_altsetting->desc.bNumEndpoints < 3)
		return -ENODEV;

	result = wa_rpipes_create(wa);
	if (result < 0)
		goto error_rpipes_create;
	wa->quirks = quirks;
	/* Fill up Data Transfer EP pointers */
	wa->dti_epd = &iface->cur_altsetting->endpoint[1].desc;
	wa->dto_epd = &iface->cur_altsetting->endpoint[2].desc;
	wa->dti_buf_size = usb_endpoint_maxp(wa->dti_epd);
	wa->dti_buf = kmalloc(wa->dti_buf_size, GFP_KERNEL);
	if (wa->dti_buf == NULL) {
		result = -ENOMEM;
		goto error_dti_buf_alloc;
	}
	result = wa_nep_create(wa, iface);
	if (result < 0) {
		dev_err(dev, "WA-CDS: can't initialize notif endpoint: %d\n",
			result);
		goto error_nep_create;
	}
	return 0;

error_nep_create:
	kfree(wa->dti_buf);
error_dti_buf_alloc:
	wa_rpipes_destroy(wa);
error_rpipes_create:
	return result;
}