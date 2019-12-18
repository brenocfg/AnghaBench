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
 int /*<<< orphan*/  sclp_con_lock ; 
 int sclp_con_suspended ; 
 int /*<<< orphan*/  sclp_console_flush () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sclp_console_suspend(void)
{
	unsigned long flags;

	spin_lock_irqsave(&sclp_con_lock, flags);
	sclp_con_suspended = 1;
	spin_unlock_irqrestore(&sclp_con_lock, flags);
	sclp_console_flush();
}