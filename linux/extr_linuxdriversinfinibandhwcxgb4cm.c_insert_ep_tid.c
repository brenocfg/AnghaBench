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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  hwtid_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  _insert_handle (TYPE_2__*,int /*<<< orphan*/ *,struct c4iw_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void insert_ep_tid(struct c4iw_ep *ep)
{
	unsigned long flags;

	spin_lock_irqsave(&ep->com.dev->lock, flags);
	_insert_handle(ep->com.dev, &ep->com.dev->hwtid_idr, ep, ep->hwtid, 0);
	spin_unlock_irqrestore(&ep->com.dev->lock, flags);
}