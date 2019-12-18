#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ib_cm_id {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __ib_cm_listen (struct ib_cm_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ cm ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_cm_listen(struct ib_cm_id *cm_id, __be64 service_id, __be64 service_mask)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cm.lock, flags);
	ret = __ib_cm_listen(cm_id, service_id, service_mask);
	spin_unlock_irqrestore(&cm.lock, flags);

	return ret;
}