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
struct smi_info {int run_to_completion; int /*<<< orphan*/  si_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_event_handler (struct smi_info*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void poll(void *send_info)
{
	struct smi_info *smi_info = send_info;
	unsigned long flags = 0;
	bool run_to_completion = smi_info->run_to_completion;

	/*
	 * Make sure there is some delay in the poll loop so we can
	 * drive time forward and timeout things.
	 */
	udelay(10);
	if (!run_to_completion)
		spin_lock_irqsave(&smi_info->si_lock, flags);
	smi_event_handler(smi_info, 10);
	if (!run_to_completion)
		spin_unlock_irqrestore(&smi_info->si_lock, flags);
}