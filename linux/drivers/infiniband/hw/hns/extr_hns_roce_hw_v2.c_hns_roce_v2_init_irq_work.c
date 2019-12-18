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
typedef  void* u32 ;
struct hns_roce_work {int /*<<< orphan*/  work; int /*<<< orphan*/  sub_type; int /*<<< orphan*/  event_type; void* cqn; void* qpn; struct hns_roce_dev* hr_dev; } ;
struct hns_roce_eq {int /*<<< orphan*/  sub_type; int /*<<< orphan*/  event_type; } ;
struct hns_roce_dev {int /*<<< orphan*/  irq_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_irq_work_handle ; 
 struct hns_roce_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_v2_init_irq_work(struct hns_roce_dev *hr_dev,
				      struct hns_roce_eq *eq,
				      u32 qpn, u32 cqn)
{
	struct hns_roce_work *irq_work;

	irq_work = kzalloc(sizeof(struct hns_roce_work), GFP_ATOMIC);
	if (!irq_work)
		return;

	INIT_WORK(&(irq_work->work), hns_roce_irq_work_handle);
	irq_work->hr_dev = hr_dev;
	irq_work->qpn = qpn;
	irq_work->cqn = cqn;
	irq_work->event_type = eq->event_type;
	irq_work->sub_type = eq->sub_type;
	queue_work(hr_dev->irq_workq, &(irq_work->work));
}