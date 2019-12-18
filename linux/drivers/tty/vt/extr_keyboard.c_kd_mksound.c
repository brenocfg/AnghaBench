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

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_handler_for_each_handle (int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kbd_handler ; 
 int /*<<< orphan*/  kd_mksound_timer ; 
 int /*<<< orphan*/  kd_sound_helper ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

void kd_mksound(unsigned int hz, unsigned int ticks)
{
	del_timer_sync(&kd_mksound_timer);

	input_handler_for_each_handle(&kbd_handler, &hz, kd_sound_helper);

	if (hz && ticks)
		mod_timer(&kd_mksound_timer, jiffies + ticks);
}