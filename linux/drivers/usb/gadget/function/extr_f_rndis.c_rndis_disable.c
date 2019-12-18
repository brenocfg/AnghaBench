#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {int dummy; } ;
struct f_rndis {TYPE_2__* notify; int /*<<< orphan*/  port; int /*<<< orphan*/  params; } ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 struct f_rndis* func_to_rndis (struct usb_function*) ; 
 int /*<<< orphan*/  gether_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rndis_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_disable (TYPE_2__*) ; 

__attribute__((used)) static void rndis_disable(struct usb_function *f)
{
	struct f_rndis		*rndis = func_to_rndis(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	if (!rndis->notify->enabled)
		return;

	DBG(cdev, "rndis deactivated\n");

	rndis_uninit(rndis->params);
	gether_disconnect(&rndis->port);

	usb_ep_disable(rndis->notify);
}