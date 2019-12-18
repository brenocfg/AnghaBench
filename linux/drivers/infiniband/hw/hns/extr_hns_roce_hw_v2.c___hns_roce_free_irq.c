#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct hns_roce_dev* eq; } ;
struct TYPE_3__ {int num_comp_vectors; int num_aeq_vectors; int num_other_vectors; } ;
struct hns_roce_dev {int /*<<< orphan*/ * irq_names; TYPE_2__ eq_table; int /*<<< orphan*/ *** irq; TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ **,struct hns_roce_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __hns_roce_free_irq(struct hns_roce_dev *hr_dev)
{
	int irq_num;
	int eq_num;
	int i;

	eq_num = hr_dev->caps.num_comp_vectors + hr_dev->caps.num_aeq_vectors;
	irq_num = eq_num + hr_dev->caps.num_other_vectors;

	for (i = 0; i < hr_dev->caps.num_other_vectors; i++)
		free_irq(hr_dev->irq[i], hr_dev);

	for (i = 0; i < eq_num; i++)
		free_irq(hr_dev->eq_table.eq[i].irq, &hr_dev->eq_table.eq[i]);

	for (i = 0; i < irq_num; i++)
		kfree(hr_dev->irq_names[i]);
}