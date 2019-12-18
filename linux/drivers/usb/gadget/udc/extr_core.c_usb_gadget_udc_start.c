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
struct usb_udc {int /*<<< orphan*/  driver; TYPE_2__* gadget; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* udc_start ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int usb_gadget_udc_start(struct usb_udc *udc)
{
	return udc->gadget->ops->udc_start(udc->gadget, udc->driver);
}