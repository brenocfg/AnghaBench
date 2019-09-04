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
struct request_queue {TYPE_1__* tag_set; scalar_t__ mq_ops; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int BLK_MQ_F_NO_SCHED ; 

__attribute__((used)) static inline bool elv_support_iosched(struct request_queue *q)
{
	if (q->mq_ops && q->tag_set && (q->tag_set->flags &
				BLK_MQ_F_NO_SCHED))
		return false;
	return true;
}