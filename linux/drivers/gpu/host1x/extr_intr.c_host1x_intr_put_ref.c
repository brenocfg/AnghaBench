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
struct host1x_waitlist {int /*<<< orphan*/  refcount; int /*<<< orphan*/  state; } ;
struct host1x_syncpt {int dummy; } ;
struct host1x {struct host1x_syncpt* syncpt; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLS_CANCELLED ; 
 int /*<<< orphan*/  WLS_PENDING ; 
 scalar_t__ WLS_REMOVED ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_load (struct host1x_syncpt*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_wait_list (struct host1x*,struct host1x_syncpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  waiter_release ; 

void host1x_intr_put_ref(struct host1x *host, unsigned int id, void *ref)
{
	struct host1x_waitlist *waiter = ref;
	struct host1x_syncpt *syncpt;

	while (atomic_cmpxchg(&waiter->state, WLS_PENDING, WLS_CANCELLED) ==
	       WLS_REMOVED)
		schedule();

	syncpt = host->syncpt + id;
	(void)process_wait_list(host, syncpt,
				host1x_syncpt_load(host->syncpt + id));

	kref_put(&waiter->refcount, waiter_release);
}