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
struct mdesc_handle {TYPE_1__* mops; int /*<<< orphan*/  list; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct mdesc_handle*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdesc_lock ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mdesc_handle*) ; 

void mdesc_release(struct mdesc_handle *hp)
{
	unsigned long flags;

	spin_lock_irqsave(&mdesc_lock, flags);
	if (refcount_dec_and_test(&hp->refcnt)) {
		list_del_init(&hp->list);
		hp->mops->free(hp);
	}
	spin_unlock_irqrestore(&mdesc_lock, flags);
}