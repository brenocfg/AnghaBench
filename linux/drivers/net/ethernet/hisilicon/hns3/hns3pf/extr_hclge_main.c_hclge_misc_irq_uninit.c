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
struct hclge_dev {TYPE_1__ misc_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_free_vector (struct hclge_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_misc_irq_uninit(struct hclge_dev *hdev)
{
	free_irq(hdev->misc_vector.vector_irq, hdev);
	hclge_free_vector(hdev, 0);
}