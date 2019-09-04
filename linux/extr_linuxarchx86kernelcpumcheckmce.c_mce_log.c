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
struct mce {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_gen_pool_add (struct mce*) ; 
 int /*<<< orphan*/  mce_irq_work ; 

void mce_log(struct mce *m)
{
	if (!mce_gen_pool_add(m))
		irq_work_queue(&mce_irq_work);
}