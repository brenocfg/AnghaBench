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
struct hclgevf_dev {scalar_t__* vector_status; int num_msi_left; int num_msi_used; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HCLGEVF_INVALID_VPORT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void hclgevf_free_vector(struct hclgevf_dev *hdev, int vector_id)
{
	if (hdev->vector_status[vector_id] == HCLGEVF_INVALID_VPORT) {
		dev_warn(&hdev->pdev->dev,
			 "vector(vector_id %d) has been freed.\n", vector_id);
		return;
	}

	hdev->vector_status[vector_id] = HCLGEVF_INVALID_VPORT;
	hdev->num_msi_left += 1;
	hdev->num_msi_used -= 1;
}