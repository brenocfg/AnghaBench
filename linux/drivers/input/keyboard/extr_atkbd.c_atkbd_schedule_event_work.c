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
struct atkbd {int /*<<< orphan*/  event_work; int /*<<< orphan*/  event_mask; scalar_t__ event_jiffies; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void atkbd_schedule_event_work(struct atkbd *atkbd, int event_bit)
{
	unsigned long delay = msecs_to_jiffies(50);

	if (time_after(jiffies, atkbd->event_jiffies + delay))
		delay = 0;

	atkbd->event_jiffies = jiffies;
	set_bit(event_bit, &atkbd->event_mask);
	mb();
	schedule_delayed_work(&atkbd->event_work, delay);
}