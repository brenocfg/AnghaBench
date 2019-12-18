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
struct TYPE_2__ {int /*<<< orphan*/  vector_irq; } ;
struct hclgevf_dev {TYPE_1__ misc_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hclgevf_dev*) ; 
 int /*<<< orphan*/  hclgevf_enable_vector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hclgevf_free_vector (struct hclgevf_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_misc_irq_uninit(struct hclgevf_dev *hdev)
{
	/* disable misc vector(vector 0) */
	hclgevf_enable_vector(&hdev->misc_vector, false);
	synchronize_irq(hdev->misc_vector.vector_irq);
	free_irq(hdev->misc_vector.vector_irq, hdev);
	hclgevf_free_vector(hdev, 0);
}