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
struct qib_pportdata {int /*<<< orphan*/  sdma_lock; } ;

/* Variables and functions */
 int qib_sdma_make_progress (struct qib_pportdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int qib_user_sdma_hwqueue_clean(struct qib_pportdata *ppd)
{
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&ppd->sdma_lock, flags);
	ret = qib_sdma_make_progress(ppd);
	spin_unlock_irqrestore(&ppd->sdma_lock, flags);

	return ret;
}