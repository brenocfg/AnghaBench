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
struct smq_policy {int /*<<< orphan*/  table; } ;
struct entry {int /*<<< orphan*/  pending_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  h_insert (int /*<<< orphan*/ *,struct entry*) ; 
 int /*<<< orphan*/  push_queue_front (struct smq_policy*,struct entry*) ; 

__attribute__((used)) static void push_front(struct smq_policy *mq, struct entry *e)
{
	h_insert(&mq->table, e);
	if (!e->pending_work)
		push_queue_front(mq, e);
}