#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  expires; } ;
struct TYPE_7__ {int /*<<< orphan*/  keylock; TYPE_1__ rx_timeout; } ;
struct ir_raw_event_ctrl {TYPE_3__ mce_kbd; TYPE_2__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_timeout; } ;
struct TYPE_6__ {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MCIR2_MASK_KEYS_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct ir_raw_event_ctrl* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 unsigned char* kbd_keycodes ; 
 TYPE_4__ mce_kbd ; 
 struct ir_raw_event_ctrl* raw ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_is_before_eq_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_kbd_rx_timeout(struct timer_list *t)
{
	struct ir_raw_event_ctrl *raw = from_timer(raw, t, mce_kbd.rx_timeout);
	unsigned char maskcode;
	unsigned long flags;
	int i;

	dev_dbg(&raw->dev->dev, "timer callback clearing all keys\n");

	spin_lock_irqsave(&raw->mce_kbd.keylock, flags);

	if (time_is_before_eq_jiffies(raw->mce_kbd.rx_timeout.expires)) {
		for (i = 0; i < 7; i++) {
			maskcode = kbd_keycodes[MCIR2_MASK_KEYS_START + i];
			input_report_key(raw->dev->input_dev, maskcode, 0);
		}

		for (i = 0; i < MCIR2_MASK_KEYS_START; i++)
			input_report_key(raw->dev->input_dev, kbd_keycodes[i],
					 0);

		input_sync(raw->dev->input_dev);
	}
	spin_unlock_irqrestore(&raw->mce_kbd.keylock, flags);
}