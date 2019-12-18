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
struct rts51x_chip {int /*<<< orphan*/  status; scalar_t__ timer_expires; int /*<<< orphan*/  rts51x_suspend_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ ss_en ; 

__attribute__((used)) static void realtek_cr_destructor(void *extra)
{
	struct rts51x_chip *chip = extra;

	if (!chip)
		return;

#ifdef CONFIG_REALTEK_AUTOPM
	if (ss_en) {
		del_timer(&chip->rts51x_suspend_timer);
		chip->timer_expires = 0;
	}
#endif
	kfree(chip->status);
}