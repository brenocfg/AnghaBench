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
struct smi_info {int timer_running; int /*<<< orphan*/  si_timer; int /*<<< orphan*/  last_timeout_jiffies; int /*<<< orphan*/  timer_can_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void smi_mod_timer(struct smi_info *smi_info, unsigned long new_val)
{
	if (!smi_info->timer_can_start)
		return;
	smi_info->last_timeout_jiffies = jiffies;
	mod_timer(&smi_info->si_timer, new_val);
	smi_info->timer_running = true;
}