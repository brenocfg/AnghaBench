#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  regs; } ;
struct timer_list {int dummy; } ;
struct ptd {int /*<<< orphan*/  dw3; int /*<<< orphan*/  dw0; } ;
struct isp1760_hcd {int atl_done_map; int /*<<< orphan*/  lock; TYPE_1__* atl_slots; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct TYPE_4__ {scalar_t__ timestamp; scalar_t__ qh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL_PTD_OFFSET ; 
 int /*<<< orphan*/  FROM_DW0_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FROM_DW3_ACTIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOT_CHECK_PERIOD ; 
 int /*<<< orphan*/  SLOT_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 TYPE_2__ errata2_timer ; 
 struct usb_hcd* errata2_timer_hcd ; 
 int /*<<< orphan*/  handle_done_ptds (struct usb_hcd*) ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ptd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void errata2_function(struct timer_list *unused)
{
	struct usb_hcd *hcd = errata2_timer_hcd;
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	int slot;
	struct ptd ptd;
	unsigned long spinflags;

	spin_lock_irqsave(&priv->lock, spinflags);

	for (slot = 0; slot < 32; slot++)
		if (priv->atl_slots[slot].qh && time_after(jiffies,
					priv->atl_slots[slot].timestamp +
					msecs_to_jiffies(SLOT_TIMEOUT))) {
			ptd_read(hcd->regs, ATL_PTD_OFFSET, slot, &ptd);
			if (!FROM_DW0_VALID(ptd.dw0) &&
					!FROM_DW3_ACTIVE(ptd.dw3))
				priv->atl_done_map |= 1 << slot;
		}

	if (priv->atl_done_map)
		handle_done_ptds(hcd);

	spin_unlock_irqrestore(&priv->lock, spinflags);

	errata2_timer.expires = jiffies + msecs_to_jiffies(SLOT_CHECK_PERIOD);
	add_timer(&errata2_timer);
}