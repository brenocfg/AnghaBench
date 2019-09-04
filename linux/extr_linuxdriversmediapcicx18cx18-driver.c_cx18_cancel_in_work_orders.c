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
struct cx18 {TYPE_1__* in_work_order; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int CX18_MAX_IN_WORK_ORDERS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx18_cancel_in_work_orders(struct cx18 *cx)
{
	int i;
	for (i = 0; i < CX18_MAX_IN_WORK_ORDERS; i++)
		cancel_work_sync(&cx->in_work_order[i].work);
}