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
typedef  long u32 ;
struct timer_list {int dummy; } ;
struct ata_port {int port_no; TYPE_1__* ops; int /*<<< orphan*/  lock; } ;
struct ata_link {int pmp; struct ata_port* ap; } ;
struct ahci_em_priv {unsigned long led_state; scalar_t__ saved_activity; scalar_t__ activity; scalar_t__ blink_policy; int /*<<< orphan*/  timer; struct ata_link* link; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* transmit_led_message ) (struct ata_port*,unsigned long,int) ;} ;

/* Variables and functions */
 scalar_t__ BLINK_OFF ; 
 unsigned long EM_MSG_LED_VALUE ; 
 unsigned long EM_MSG_LED_VALUE_ACTIVITY ; 
 unsigned long EM_MSG_LED_VALUE_ON ; 
 struct ahci_em_priv* emp ; 
 struct ahci_em_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,unsigned long,int) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void ahci_sw_activity_blink(struct timer_list *t)
{
	struct ahci_em_priv *emp = from_timer(emp, t, timer);
	struct ata_link *link = emp->link;
	struct ata_port *ap = link->ap;

	unsigned long led_message = emp->led_state;
	u32 activity_led_state;
	unsigned long flags;

	led_message &= EM_MSG_LED_VALUE;
	led_message |= ap->port_no | (link->pmp << 8);

	/* check to see if we've had activity.  If so,
	 * toggle state of LED and reset timer.  If not,
	 * turn LED to desired idle state.
	 */
	spin_lock_irqsave(ap->lock, flags);
	if (emp->saved_activity != emp->activity) {
		emp->saved_activity = emp->activity;
		/* get the current LED state */
		activity_led_state = led_message & EM_MSG_LED_VALUE_ON;

		if (activity_led_state)
			activity_led_state = 0;
		else
			activity_led_state = 1;

		/* clear old state */
		led_message &= ~EM_MSG_LED_VALUE_ACTIVITY;

		/* toggle state */
		led_message |= (activity_led_state << 16);
		mod_timer(&emp->timer, jiffies + msecs_to_jiffies(100));
	} else {
		/* switch to idle */
		led_message &= ~EM_MSG_LED_VALUE_ACTIVITY;
		if (emp->blink_policy == BLINK_OFF)
			led_message |= (1 << 16);
	}
	spin_unlock_irqrestore(ap->lock, flags);
	ap->ops->transmit_led_message(ap, led_message, 4);
}