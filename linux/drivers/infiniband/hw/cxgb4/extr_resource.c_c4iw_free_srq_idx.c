#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cur; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__ srqt; } ;
struct TYPE_4__ {int /*<<< orphan*/  srq_table; } ;
struct c4iw_rdev {TYPE_3__ stats; TYPE_1__ resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_id_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void c4iw_free_srq_idx(struct c4iw_rdev *rdev, int idx)
{
	c4iw_id_free(&rdev->resource.srq_table, idx);
	mutex_lock(&rdev->stats.lock);
	rdev->stats.srqt.cur--;
	mutex_unlock(&rdev->stats.lock);
}