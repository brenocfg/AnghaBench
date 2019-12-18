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
struct iu_entry {TYPE_2__* target; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct TYPE_4__ {TYPE_1__ iu_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_in_locked (int /*<<< orphan*/ *,void*,int,int /*<<< orphan*/ *) ; 

void srp_iu_put(struct iu_entry *iue)
{
	kfifo_in_locked(&iue->target->iu_queue.queue, (void *)&iue,
			sizeof(void *), &iue->target->iu_queue.lock);
}