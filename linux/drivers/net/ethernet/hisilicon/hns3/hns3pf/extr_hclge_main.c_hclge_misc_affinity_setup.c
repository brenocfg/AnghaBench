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
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  notify; } ;
struct TYPE_3__ {int /*<<< orphan*/  vector_irq; } ;
struct hclge_dev {TYPE_2__ affinity_notify; TYPE_1__ misc_vector; int /*<<< orphan*/  affinity_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_irq_affinity_notify ; 
 int /*<<< orphan*/  hclge_irq_affinity_release ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_affinity_notifier (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void hclge_misc_affinity_setup(struct hclge_dev *hdev)
{
	irq_set_affinity_hint(hdev->misc_vector.vector_irq,
			      &hdev->affinity_mask);

	hdev->affinity_notify.notify = hclge_irq_affinity_notify;
	hdev->affinity_notify.release = hclge_irq_affinity_release;
	irq_set_affinity_notifier(hdev->misc_vector.vector_irq,
				  &hdev->affinity_notify);
}