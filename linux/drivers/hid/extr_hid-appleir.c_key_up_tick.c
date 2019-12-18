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
struct timer_list {int dummy; } ;
struct hid_device {int dummy; } ;
struct appleir {int /*<<< orphan*/  lock; scalar_t__ current_key; struct hid_device* hid; } ;

/* Variables and functions */
 struct appleir* appleir ; 
 struct appleir* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_up (struct hid_device*,struct appleir*,scalar_t__) ; 
 int /*<<< orphan*/  key_up_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void key_up_tick(struct timer_list *t)
{
	struct appleir *appleir = from_timer(appleir, t, key_up_timer);
	struct hid_device *hid = appleir->hid;
	unsigned long flags;

	spin_lock_irqsave(&appleir->lock, flags);
	if (appleir->current_key) {
		key_up(hid, appleir, appleir->current_key);
		appleir->current_key = 0;
	}
	spin_unlock_irqrestore(&appleir->lock, flags);
}