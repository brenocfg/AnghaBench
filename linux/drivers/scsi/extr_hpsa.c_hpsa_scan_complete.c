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
struct ctlr_info {int scan_finished; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  scan_wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hpsa_scan_complete(struct ctlr_info *h)
{
	unsigned long flags;

	spin_lock_irqsave(&h->scan_lock, flags);
	h->scan_finished = 1;
	wake_up(&h->scan_wait_queue);
	spin_unlock_irqrestore(&h->scan_lock, flags);
}