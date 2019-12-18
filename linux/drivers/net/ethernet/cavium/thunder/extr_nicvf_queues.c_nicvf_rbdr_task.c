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
struct nicvf {int rb_work_scheduled; int /*<<< orphan*/  rbdr_work; scalar_t__ rb_alloc_fail; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  nicvf_refill_rbdr (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nicvf_rbdr_task(unsigned long data)
{
	struct nicvf *nic = (struct nicvf *)data;

	nicvf_refill_rbdr(nic, GFP_ATOMIC);
	if (nic->rb_alloc_fail) {
		nic->rb_work_scheduled = true;
		schedule_delayed_work(&nic->rbdr_work, msecs_to_jiffies(10));
	}
}