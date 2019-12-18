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
struct usb_hcd {int dummy; } ;
struct fotg210_hcd {int shutdown; int /*<<< orphan*/  hrtimer; int /*<<< orphan*/  lock; scalar_t__ enabled_hrtimer_events; int /*<<< orphan*/  rh_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOTG210_RH_STOPPING ; 
 int /*<<< orphan*/  fotg210_silence_controller (struct fotg210_hcd*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_shutdown(struct usb_hcd *hcd)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	spin_lock_irq(&fotg210->lock);
	fotg210->shutdown = true;
	fotg210->rh_state = FOTG210_RH_STOPPING;
	fotg210->enabled_hrtimer_events = 0;
	spin_unlock_irq(&fotg210->lock);

	fotg210_silence_controller(fotg210);

	hrtimer_cancel(&fotg210->hrtimer);
}