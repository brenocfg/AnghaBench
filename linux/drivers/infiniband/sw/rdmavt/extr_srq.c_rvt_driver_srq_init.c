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
struct rvt_dev_info {scalar_t__ n_srqs_allocated; int /*<<< orphan*/  n_srqs_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void rvt_driver_srq_init(struct rvt_dev_info *rdi)
{
	spin_lock_init(&rdi->n_srqs_lock);
	rdi->n_srqs_allocated = 0;
}