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
struct request_queue {scalar_t__ mq_ops; } ;
struct hd_struct {scalar_t__ partno; int /*<<< orphan*/ * in_flight; } ;
struct TYPE_3__ {int /*<<< orphan*/ * in_flight; } ;
struct TYPE_4__ {TYPE_1__ part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_2__* part_to_disk (struct hd_struct*) ; 

void part_inc_in_flight(struct request_queue *q, struct hd_struct *part, int rw)
{
	if (q->mq_ops)
		return;

	atomic_inc(&part->in_flight[rw]);
	if (part->partno)
		atomic_inc(&part_to_disk(part)->part0.in_flight[rw]);
}