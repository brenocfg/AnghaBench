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
struct bfq_queue {int dummy; } ;
struct bfq_group {struct bfq_queue* async_idle_bfqq; struct bfq_queue*** async_bfqq; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
#define  IOPRIO_CLASS_BE 131 
#define  IOPRIO_CLASS_IDLE 130 
#define  IOPRIO_CLASS_NONE 129 
#define  IOPRIO_CLASS_RT 128 
 int IOPRIO_NORM ; 

__attribute__((used)) static struct bfq_queue **bfq_async_queue_prio(struct bfq_data *bfqd,
					       struct bfq_group *bfqg,
					       int ioprio_class, int ioprio)
{
	switch (ioprio_class) {
	case IOPRIO_CLASS_RT:
		return &bfqg->async_bfqq[0][ioprio];
	case IOPRIO_CLASS_NONE:
		ioprio = IOPRIO_NORM;
		/* fall through */
	case IOPRIO_CLASS_BE:
		return &bfqg->async_bfqq[1][ioprio];
	case IOPRIO_CLASS_IDLE:
		return &bfqg->async_idle_bfqq;
	default:
		return NULL;
	}
}