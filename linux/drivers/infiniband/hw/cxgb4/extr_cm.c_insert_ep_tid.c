#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* dev; } ;
struct c4iw_ep {TYPE_1__ com; int /*<<< orphan*/  hwtid; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwtids; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __xa_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct c4iw_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int insert_ep_tid(struct c4iw_ep *ep)
{
	unsigned long flags;
	int err;

	xa_lock_irqsave(&ep->com.dev->hwtids, flags);
	err = __xa_insert(&ep->com.dev->hwtids, ep->hwtid, ep, GFP_KERNEL);
	xa_unlock_irqrestore(&ep->com.dev->hwtids, flags);

	return err;
}