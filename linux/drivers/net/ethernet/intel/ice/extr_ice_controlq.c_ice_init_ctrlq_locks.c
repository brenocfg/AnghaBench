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
struct ice_ctl_q_info {int /*<<< orphan*/  rq_lock; int /*<<< orphan*/  sq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_init_ctrlq_locks(struct ice_ctl_q_info *cq)
{
	mutex_init(&cq->sq_lock);
	mutex_init(&cq->rq_lock);
}