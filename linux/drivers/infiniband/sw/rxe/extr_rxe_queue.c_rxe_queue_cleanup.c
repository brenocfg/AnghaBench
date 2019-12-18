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
struct rxe_queue {int /*<<< orphan*/  buf; TYPE_1__* ip; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rxe_queue*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_mmap_release ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void rxe_queue_cleanup(struct rxe_queue *q)
{
	if (q->ip)
		kref_put(&q->ip->ref, rxe_mmap_release);
	else
		vfree(q->buf);

	kfree(q);
}