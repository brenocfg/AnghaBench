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
struct irq_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mce_schedule_work () ; 

__attribute__((used)) static void mce_irq_work_cb(struct irq_work *entry)
{
	mce_schedule_work();
}