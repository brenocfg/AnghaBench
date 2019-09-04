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
struct mbox_test_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int mbox_data_ready ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool mbox_test_message_data_ready(struct mbox_test_device *tdev)
{
	bool data_ready;
	unsigned long flags;

	spin_lock_irqsave(&tdev->lock, flags);
	data_ready = mbox_data_ready;
	spin_unlock_irqrestore(&tdev->lock, flags);

	return data_ready;
}