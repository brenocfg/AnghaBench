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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rn5t618_trigger_poweroff_sequence (int) ; 

__attribute__((used)) static int rn5t618_restart(struct notifier_block *this,
			    unsigned long mode, void *cmd)
{
	rn5t618_trigger_poweroff_sequence(true);

	/*
	 * Re-power factor detection on PMIC side is not instant. 1ms
	 * proved to be enough time until reset takes effect.
	 */
	mdelay(1);

	return NOTIFY_DONE;
}