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
struct ipmi_smi {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPMI_TIMEOUT_JIFFIES ; 
 int /*<<< orphan*/  ipmi_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void need_waiter(struct ipmi_smi *intf)
{
	/* Racy, but worst case we start the timer twice. */
	if (!timer_pending(&ipmi_timer))
		mod_timer(&ipmi_timer, jiffies + IPMI_TIMEOUT_JIFFIES);
}