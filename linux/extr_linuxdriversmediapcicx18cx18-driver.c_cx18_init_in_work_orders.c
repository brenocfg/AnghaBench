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
struct cx18 {TYPE_1__* in_work_order; int /*<<< orphan*/  epu_debug_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  str; struct cx18* cx; } ;

/* Variables and functions */
 int CX18_MAX_IN_WORK_ORDERS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_in_work_handler ; 

__attribute__((used)) static void cx18_init_in_work_orders(struct cx18 *cx)
{
	int i;
	for (i = 0; i < CX18_MAX_IN_WORK_ORDERS; i++) {
		cx->in_work_order[i].cx = cx;
		cx->in_work_order[i].str = cx->epu_debug_str;
		INIT_WORK(&cx->in_work_order[i].work, cx18_in_work_handler);
	}
}