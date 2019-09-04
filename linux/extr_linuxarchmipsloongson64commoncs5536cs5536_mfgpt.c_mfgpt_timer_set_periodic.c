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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE ; 
 int /*<<< orphan*/  MFGPT0_CMP2 ; 
 int /*<<< orphan*/  MFGPT0_CNT ; 
 int /*<<< orphan*/  enable_mfgpt0_counter () ; 
 int /*<<< orphan*/  mfgpt_lock ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mfgpt_timer_set_periodic(struct clock_event_device *evt)
{
	raw_spin_lock(&mfgpt_lock);

	outw(COMPARE, MFGPT0_CMP2);	/* set comparator2 */
	outw(0, MFGPT0_CNT);		/* set counter to 0 */
	enable_mfgpt0_counter();

	raw_spin_unlock(&mfgpt_lock);
	return 0;
}