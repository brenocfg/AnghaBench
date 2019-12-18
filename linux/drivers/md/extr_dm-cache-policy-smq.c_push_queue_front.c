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
struct smq_policy {int /*<<< orphan*/  clean; int /*<<< orphan*/  dirty; } ;
struct entry {scalar_t__ dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  q_push_front (int /*<<< orphan*/ *,struct entry*) ; 

__attribute__((used)) static void push_queue_front(struct smq_policy *mq, struct entry *e)
{
	if (e->dirty)
		q_push_front(&mq->dirty, e);
	else
		q_push_front(&mq->clean, e);
}