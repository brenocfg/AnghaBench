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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct isp1760_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/  vbus_timer; TYPE_1__ gadget; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_MODE ; 
 int DC_VBUSSTAT ; 
 scalar_t__ ISP1760_VBUS_POLL_INTERVAL ; 
 scalar_t__ USB_STATE_POWERED ; 
 struct isp1760_udc* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1760_udc_disconnect (struct isp1760_udc*) ; 
 int isp1760_udc_read (struct isp1760_udc*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isp1760_udc* udc ; 
 int /*<<< orphan*/  vbus_timer ; 

__attribute__((used)) static void isp1760_udc_vbus_poll(struct timer_list *t)
{
	struct isp1760_udc *udc = from_timer(udc, t, vbus_timer);
	unsigned long flags;

	spin_lock_irqsave(&udc->lock, flags);

	if (!(isp1760_udc_read(udc, DC_MODE) & DC_VBUSSTAT))
		isp1760_udc_disconnect(udc);
	else if (udc->gadget.state >= USB_STATE_POWERED)
		mod_timer(&udc->vbus_timer,
			  jiffies + ISP1760_VBUS_POLL_INTERVAL);

	spin_unlock_irqrestore(&udc->lock, flags);
}