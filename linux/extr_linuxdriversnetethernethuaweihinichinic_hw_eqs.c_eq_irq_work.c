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
struct work_struct {int dummy; } ;
struct hinic_eq_work {struct hinic_eq* data; } ;
struct hinic_eq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_irq_handler (struct hinic_eq*) ; 
 struct hinic_eq_work* work_to_aeq_work (struct work_struct*) ; 

__attribute__((used)) static void eq_irq_work(struct work_struct *work)
{
	struct hinic_eq_work *aeq_work = work_to_aeq_work(work);
	struct hinic_eq *aeq;

	aeq = aeq_work->data;
	eq_irq_handler(aeq);
}